/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:02:44 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/25 18:00:16 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	pass_selected(int bit, t_stacks *stacks, int mode)
{
	int	nb;
	int last_bits;
	int	parity;

	nb = int_content(stacks->a);
	last_bits = get_last_bits(nb, bit);
	parity = get_parity(nb, bit);
	if ((mode & FIRST_P && ((last_bits == 2 && parity) || last_bits == 3))
		|| (mode & SECOND_P && ((last_bits == 1 && parity) || last_bits == 4)))
	{
		
	}
	if ((mode & FIRST_P && ((last_bits == 3 && !parity) || last_bits == 2))
		|| (mode & SECOND_P && ((last_bits == 4 && !parity) || last_bits == 1)))
	{
		
	}
	else
	{

	}
}

void	radix(int bit, t_stacks *stacks, int len, int mode)
{
	int	i;
	int nb_still;

	i = 0;
	while (i < len)
	{
		nb_still = pass_selected(bit, stacks, mode | FIRST_P);
		i++;
	}
	i = 0;
	while (i < nb_still)
	{
		pass_selected(bit, stacks, mode | SECOND_P);
		i++;
	}
}
