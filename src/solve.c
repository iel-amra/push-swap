/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:42:50 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/25 14:51:38 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

static int	get_nb_bit(int nb)
{
	int	n_bit;

	n_bit = 1;
	while (nb > 0)
	{
		n_bit++;
		nb /= 2;
	}
	return (0);
}

static int	get_nb_max(t_lst *stack)
{
	int	nb_max;
	int	nb;

	nb_max = 0;
	while (*stack)
	{
		nb = int_content(stack);
		if (nb > nb_max)
			nb_max = nb;
	}
	return (nb_max);
}	

int	solve(t_stacks *stacks)
{
	int	nb_bit_max;
	int	i;
	int	nb_max;

	nb_max = get_nb_max(stacks->a);
	nb_bit_max = get_nb_bit(nb_max);
	i = nb_bit_max % 4;
	while (i < nb_bit_max)
	{
		radix(i, *stacks, A_TO_B);
		radix(i + 2, *stacks, nb_max + 1, B_TO_A);	
		i += 4;
	}
	return (0);
}
