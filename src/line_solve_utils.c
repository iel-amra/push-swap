/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_solve_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:20:47 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:20:48 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	prep_second_step(t_stacks *stacks, int *data, int *line)
{
	int	i;
	int	moved;

	moved = 0;
	i = line[data[0]];
	if (i >= data[0] - 1 || line[i] > line[i + 1])
		return (moved);
	while (int_content(stacks->b) > int_content(stacks->a)
		&& is_in_tab(line, int_content(stacks->a), i)
		&& (int_content(stacks->a) != line[0] || !moved))
	{
		move(stacks, RA, data[1]);
		moved = 1;
	}
	return ((moved && int_content(stacks->a) == line[0])
		+ (!moved && int_content(stacks->a) == line[0]) * -1);
}

void	move_downward(t_stacks *stacks, int verbose, int *line, int *moved)
{
	int	last;

	if (int_content(stacks->a) == line[0] && *moved == 0)
		*moved = -1;
	*moved = 0;
	move(stacks, RRA, verbose);
	last = int_content(ft_lstlast(stacks->a));
	while (stacks->b && int_content(stacks->a) > int_content(stacks->b)
		&& (int_content(stacks->a) <= line[0]
			|| last < int_content(stacks->b)))
		move(stacks, PA, verbose);
}

int	get_smallest(int *tab, int nb)
{
	int	smallest;
	int	i;

	smallest = tab[0];
	i = 1;
	while (i < nb)
	{
		if (tab[i] < smallest)
			smallest = tab[i];
		i++;
	}
	return (smallest);
}

int	get_best_correc(t_stacks *stacks, int nb)
{
	int			i;
	int			j;
	t_stacks	*copy;
	int			ret;

	i = 2;
	ret = -1;
	while (ret == -1)
	{
		copy = copy_stacks(stacks);
		if (!copy)
			return (1);
		if (line_solve(copy, i, 0) == 0)
		{
			j = 0;
			while (j++ < i)
				move(copy, RRA, 0);
			ret = line_solve(copy, nb, 0);
		}
		free_stacks(copy);
		i++;
	}
	i--;
	return (i);
}
