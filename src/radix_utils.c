/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:17:24 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/30 12:22:42 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	radix_push(t_stacks *stacks, int mode)
{
	if (mode | A_TO_B)
		move(stacks, PA, 1);
	else
		move(stacks, PB, 1);
}

void radix_reverse_push(t_stacks *stacks, int mode)
{
	if (mode | A_TO_B)
	{
		move(stacks, PA, 1);
		move(stacks, RB, 1);
	}
	else
	{
		move(stacks, PB, 1);
		move(stacks, RA, 1);
	}
}

