/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:13:52 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/16 15:48:30 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	move(t_stacks *stacks, int action, int verbose)
{
	if (action == PA && verbose && stacks->b)
		ft_printf("pa\n");
	if (action == PA && stacks->b)
		px(&stacks->a, &stacks->b);
	if (action == PB && verbose && stacks->a)
		ft_printf("pb\n");
	if (action == PB && stacks->a)
		px(&stacks->b, &stacks->a);
	if (action == SA && verbose && stacks->a && stacks->a->next)
		ft_printf("sa\n");
	if ((action == SA || action == SS) && stacks->a && stacks->a->next)
		sx(&stacks->a);
	if (action == SB && verbose && stacks->b && stacks->b->next)
		ft_printf("sb\n");
	if ((action == SB || action == SS) && stacks->b && stacks->b->next)
		sx(&stacks->b);
	if (action == SS && verbose
		&& ((stacks->a && stacks->a->next) || (stacks->b && stacks->b->next)))
		ft_printf("ss\n");
	move_rotations(stacks, action, verbose);
	return (1);
}

void	move_rotations(t_stacks *stacks, int action, int verbose)
{
	if (action == RA && verbose && stacks->a && stacks->a->next)
		ft_printf("ra\n");
	if ((action == RA || action == RR) && stacks->a && stacks->a->next)
		rx(&stacks->a);
	if (action == RB && verbose && stacks->b && stacks->b->next)
		ft_printf("rb\n");
	if ((action == RB || action == RR) && stacks->b && stacks->b->next)
		rx(&stacks->b);
	if (action == RR && verbose
		&& ((stacks->a && stacks->a->next) || (stacks->b && stacks->b->next)))
		ft_printf("rr\n");
	if (action == RRA && verbose && stacks->a && stacks->a->next)
		ft_printf("rra\n");
	if ((action == RRA || action == RRR) && stacks->a && stacks->a->next)
		rrx(&stacks->a);
	if (action == RRB && verbose && stacks->b && stacks->b->next)
		ft_printf("rrb\n");
	if ((action == RRB || action == RRR) && stacks->b && stacks->b->next)
		rrx(&stacks->b);
	if (action == RRR && verbose
		&& ((stacks->a && stacks->a->next) || (stacks->b && stacks->b->next)))
		ft_printf("rrr\n");
}

int	get_opposite_move(int i)
{
	if (i < PB)
		return (i + 4);
	if (i < SA)
		return (i - 4);
	return (i);
}
