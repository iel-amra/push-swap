/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:42:50 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/10 17:57:16 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int nb, int exp)
{
	int	res;

	res = 1;
	while (exp-- > 0)
		res *= nb;
	return (res);
}

static int	get_nb_bit(int nb)
{
	int	n_bit;

	if (nb == 0)
		return (1);
	n_bit = 0;
	while (nb > 0)
	{
		n_bit++;
		nb /= 2;
	}
	return (n_bit);
}

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

int	solve(t_stacks *stacks)
{
	int	nb_bit_max;
	int	i;
	int	nb_max;
	char	*brute;

	nb_max = get_nb_max(stacks->a);
	nb_bit_max = get_nb_bit(nb_max);
	
	if (nb_max + 1 <= 8)
	{
		brute = brute_force(nb_max + 1, 0);
		if (!brute)
			return (1);
		stacks->nb = nb_max + 1;
		char best_move = *get_best_move(stacks, brute);
		while (best_move != SORTED)
		{
			move(stacks, best_move, 1);
			best_move = *get_best_move(stacks, brute);
		}
		free(brute);
	}
	i =  0;//nb_bit_max % 4;
	while (i < nb_bit_max)
	{
		radix(i, stacks, nb_max + 1, A_TO_B);
		radix(i + 2, stacks, nb_max + 1,
			B_TO_A | LAST * (i + 4 >= nb_bit_max));	
		i += 4;
	}
	return (0);
}
