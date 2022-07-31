/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:41:04 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/30 12:24:59 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_parity(int nb, int bit)
{
	int	parity;

	nb >> bit + 3;
	parity = 0;
	while (nb > 0)
	{
		nb /= 4;
		parity = 1 - parity;
	}
	return (parity);
}

static int	get_last_bit(int nb, int bit)
{
	nb >> bit;
	return (nb % 4);
}

static int	pass_selected(int bit, t_stacks *stacks, int mode)
{
	int	nb;
	int	last_bits;
	int	parity;

	nb = int_content(stacks->a);
	last_bits = get_last_bits(nb, bit);
	parity = get_parity(nb, bit);
	if ((mode & FIRST_P && ((last_bits == 2 && parity) || last_bits == 3))
		|| (mode & SECOND_P && ((last_bits == 1 && parity) || last_bits == 4)))
	radix_push(stacks, mode);	
	else if ((mode & FIRST_P && ((last_bits == 3 && !parity) || last_bits == 2))
		|| (mode & SECOND_P && ((last_bits == 4 && !parity) || last_bits == 1)))
	radix_reverse_push(stacks, mode);
	else
	{
		if (mode | A_TO_B)
			move(stacks, RA, 1);
		else
			move(stacks, RB, 1);
		return (1);
	}
	return (0);
}

void	radix(int bit, t_stacks *stacks, int len, int mode)
{
	int	i;
	int	nb_still;

	i = 0;
	nb_still = 0;
	while (i < len)
	{
		nb_still += pass_selected(bit, stacks, mode | FIRST_P);
		i++;
	}
	i = 0;
	while (i < nb_still)
	{
		pass_selected(bit, stacks, mode | SECOND_P);
		i++;
	}
}
