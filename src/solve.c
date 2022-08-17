/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:42:50 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/16 16:17:35 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

static int	get_nb_max(t_list *stack)
{
	int	nb_max;
	int	nb;

	nb_max = 0;
	while (stack)
	{
		nb = int_content(stack);
		if (nb > nb_max)
			nb_max = nb;
		stack = stack->next;
	}
	return (nb_max);
}	

int	solve_brute(t_stacks *stacks, int nb)
{
	char	best_move;
	char	*brute;

	brute = brute_force(nb, 0);
	if (!brute)
		return (1);
	stacks->nb = nb;
	best_move = *get_best_move(stacks, brute);
	while (best_move != SORTED)
	{
		move(stacks, best_move, 1);
		best_move = *get_best_move(stacks, brute);
	}
	free(brute);
	return (0);
}

int	solve(t_stacks *stacks)
{
	int	nb_bit_max;
	int	i;
	int	nb_max;
	int	nb_line;
	int	len_line;	

	nb_max = get_nb_max(stacks->a) + 1;
	nb_bit_max = get_nb_bit(nb_max - 1);
	if (nb_max < 8)
		return (solve_brute(stacks, nb_max));
	i = nb_bit_max % 4;
	while (i < nb_bit_max)
	{
		radix(i, stacks, nb_max, A_TO_B);
		radix(i + 2, stacks, nb_max, B_TO_A | LAST * (i + 4 >= nb_bit_max));
		i += 4;
	}
	len_line = ft_pow(2, nb_bit_max % 4);
	nb_line = nb_max / len_line;
	i = 0;
	while (i++ < nb_line)
		best_line_solve(stacks, len_line);
	if (nb_max % len_line && best_line_solve(stacks, nb_max % len_line))
		return (1);
	return (0);
}
