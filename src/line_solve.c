/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:19:36 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:20:00 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	line_first_step(t_stacks *stacks, int *data, int *line, int best_sa)
{
	int	i;
	int	j;

	i = 0;
	j = line[data[0]];
	while (j < data[0] || best_sa >> i)
	{
		if (best_sa >> i & 1)
			move(stacks, SA, data[1]);
		i++;
		if (j < data[0] && line[j] == int_content(stacks->a))
		{
			move(stacks, PB, data[1]);
			j++;
		}
		else if (j < data[0] || best_sa >> i)
			move(stacks, RA, data[1]);
	}
}

void	line_second(t_stacks *stacks, int *data, int *line, int moved)
{
	int	sep;
	int	last;

	sep = line[data[0]];
	if (sep == data[0])
		return ;
	last = int_content(ft_lstlast(stacks->a));
	if ((moved == 1 || !is_in_tab(line, int_content(stacks->a), sep))
		&& stacks->b && last < int_content(stacks->b))
	{
		moved = 0;
		move(stacks, PA, data[1]);
	}
	while (stacks->b && moved != 1
		&& int_content(stacks->a) > int_content(stacks->b)
		&& (moved == -1 || last < int_content(stacks->b)))
		move(stacks, PA, data[1]);
	while (moved != -1 && is_in_tab(line, last, sep)
		&& stacks->b && last > int_content(stacks->b))
	{
		move_downward(stacks, data[1], line, &moved);
		last = int_content(ft_lstlast(stacks->a));
	}
}

void	line_third_step(t_stacks *stacks, int *data, int *line)
{
	int	smallest;

	smallest = get_smallest(line, data[0]);
	if (stacks->b && (!stacks->a
			|| !is_in_tab(line, int_content(stacks->a), data[0])
			|| int_content(stacks->b) < int_content(stacks->a)))
		move(stacks, PA, data[1]);
	move(stacks, RA, data[1]);
	while (!stacks->a || stacks->b
		|| (is_in_tab(line, int_content(stacks->a), data[0])
			&& int_content(stacks->a) != smallest))
	{
		if (stacks->b && (!stacks->a
				|| !is_in_tab(line, int_content(stacks->a), data[0])
				|| int_content(stacks->a) == smallest
				|| int_content(stacks->b) < int_content(stacks->a)))
			move(stacks, PA, data[1]);
		move(stacks, RA, data[1]);
	}
}

int	best_line_solve(t_stacks *stacks, int nb)
{
	int	ret;
	int	correc;
	int	i;

	ret = line_solve(stacks, nb, 1);
	if (ret >= 0)
		return (ret);
	correc = get_best_correc(stacks, nb);
	if (line_solve(stacks, correc, 1))
		return (1);
	i = 0;
	while (i++ < correc)
		move(stacks, RRA, 1);
	if (line_solve(stacks, nb, 1))
		return (1);
	return (0);
}

int	line_solve(t_stacks *stacks, int nb, int verbose)
{
	int	best_sa;
	int	*line;
	int	moved;
	int	data[2];

	data[0] = nb;
	data[1] = verbose;
	get_best_sa(stacks, nb, &line, &best_sa);
	free(line);
	move_sa_binary(stacks, nb, best_sa, 0);
	if (score_line(stacks, nb, &line) == -1)
	{
		move_sa_binary(stacks, nb, best_sa, 1);
		free(line);
		return (-1);
	}
	move_sa_binary(stacks, nb, best_sa, 1);
	line_first_step(stacks, data, line, best_sa);
	moved = prep_second_step(stacks, data, line);
	line_second(stacks, data, line, moved);
	line_third_step(stacks, data, line);
	free(line);
	return (0);
}
