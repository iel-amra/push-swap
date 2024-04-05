/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:19:36 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/16 16:33:26 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	line_first_step(t_stacks *stacks, int verbose, int *line, int best_sa)
{
	int	i;
	int	j;
	int	coups;

	coups = 0;
	i = 0;
	j = line[stacks->nb];
	while (j < stacks->nb || best_sa >> i)
	{
		if (best_sa >> i & 1)
			coups += move(stacks, SA, verbose);
		i++;
		if (j < stacks->nb && line[j] == int_content(stacks->a))
		{
			coups += move(stacks, PB, verbose);
			j++;
		}
		else if (j < stacks->nb || best_sa >> i)
			coups += move(stacks, RA, verbose);
	}
	return (coups);
}

int	line_second(t_stacks *stacks, int verbose, int *line, int moved)
{
	int	last;
	int	coups;

	coups = 0;
	if (line[stacks->nb] == stacks->nb)
		return (coups);
	last = int_content(ft_lstlast(stacks->a));
	if ((moved == 1
			|| !is_in_tab(line, int_content(stacks->a), line[stacks->nb]))
		&& stacks->b && last < int_content(stacks->b))
	{
		moved = 0;
		coups += move(stacks, PA, verbose);
	}
	while (stacks->b && moved != 1
		&& int_content(stacks->a) > int_content(stacks->b)
		&& (moved == -1 || last < int_content(stacks->b)))
		coups += move(stacks, PA, verbose);
	while (moved != -1 && is_in_tab(line, last, line[stacks->nb])
		&& stacks->b && last > int_content(stacks->b))
	{
		coups += move_downward(stacks, verbose, line, &moved);
		last = int_content(ft_lstlast(stacks->a));
	}
	return (coups);
}

int	line_third_step(t_stacks *stacks, int verbose, int *line)
{
	int	smallest;
	int	coups;

	coups = 0;
	smallest = get_smallest(line, stacks->nb);
	if (stacks->b && (!stacks->a
			|| !is_in_tab(line, int_content(stacks->a), stacks->nb)
			|| int_content(stacks->b) < int_content(stacks->a)))
		coups += move(stacks, PA, verbose);
	coups += move(stacks, RA, verbose);
	while (!stacks->a || stacks->b
		|| (is_in_tab(line, int_content(stacks->a), stacks->nb)
			&& int_content(stacks->a) != smallest))
	{
		if (stacks->b && (!stacks->a
				|| !is_in_tab(line, int_content(stacks->a), stacks->nb)
				|| int_content(stacks->a) == smallest
				|| int_content(stacks->b) < int_content(stacks->a)))
				coups += move(stacks, PA, verbose);
		coups += move(stacks, RA, verbose);
	}
	return (coups);
}

int	best_line_solve(t_stacks *stacks, int nb)
{
	int			ret;
	int			correc;
	int			i;

	ret = line_solve(stacks, nb, 1);
	if (ret >= 0)
		return (ret);
	correc = get_best_correc(stacks, nb);
	if (line_solve(stacks, correc, 1) == -2)
		return (1);
	i = 0;
	while (i++ < correc)
		move(stacks, RRA, 1);
	if (line_solve(stacks, nb, 1) == -2)
		return (1);
	return (0);
}

int	line_solve(t_stacks *stacks, int nb, int verbose)
{
	int	best_sa;
	int	*line;

	stacks->nb = nb;
	get_best_sa(stacks, nb, &line, &best_sa);
	free(line);
	move_sa_binary(stacks, nb, best_sa, 0);
	if (score_line(stacks, nb, &line, best_sa) == 1000)
	{
		move_sa_binary(stacks, nb, best_sa, 1);
		free(line);
		return (-1);
	}
	move_sa_binary(stacks, nb, best_sa, 1);
	line_solve_params(stacks, verbose, line, best_sa);
	free(line);
	return (0);
}
