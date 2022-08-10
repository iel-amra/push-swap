void	move(t_stacks *stacks, int action, int verbose)
{
	/*
	ft_dprintf(2, "Before : diff = %i, nb = %i\n", stacks->diff, stacks->nb);
	put_stacks(*stacks);
	*/
	if (action == PA && verbose && stacks->b)
		ft_printf("pa\n");
	if (action == PA && stacks->b)
	{
		stacks->nb++;
		stacks->total++;
		px(&stacks->a, &stacks->b);
	}
	if (action == PB && verbose && stacks->a)
		ft_printf("pb\n");
	if (action == PB && stacks->a)
	{
		stacks->nb--;
		stacks->total--;
		px(&stacks->b, &stacks->a);
	}
	if (action == SA && verbose && stacks->a && stacks->a->next)
		ft_printf("sa\n");
	if ((action == SA || action == SS) && stacks->a && stacks->a->next)
		sx(&stacks->a);
	if (action == SB && verbose && stacks->b && stacks->b->next)
		ft_printf("sb\n");
	if ((action == SB || action == SS) && stacks->b && stacks->b->next)
		sx(&stacks->b);
	if (action == SS && verbose &&
			((stacks->a && stacks->a->next) || (stacks->b && stacks->b->next)))
		ft_printf("ss\n");

	if (action == RA && verbose && stacks->a && stacks->a->next)
		ft_printf("ra\n");
	if ((action == RA || action == RR) && stacks->a && stacks->a->next)
	{
		if (stacks->diff < stacks->nb - 1)
			stacks->diff++;
		rx(&stacks->a);
	}
	if (action == RB && verbose && stacks->b && stacks->b->next)
		ft_printf("rb\n");
	if ((action == RB || action == RR) && stacks->b && stacks->b->next)
		rx(&stacks->b);
	if (action == RR && verbose &&
			((stacks->a && stacks->a->next) || (stacks->b && stacks->b->next)))
		ft_printf("rr\n");

	if (action == RRA && verbose && stacks->a && stacks->a->next)
		ft_printf("rra\n");
	if ((action == RRA || action == RRR) && stacks->a && stacks->a->next)
	{
		if (stacks->diff > 0)
			stacks->diff--;
		rrx(&stacks->a);
	}
	if (action == RRB && verbose && stacks->b && stacks->b->next)
		ft_printf("rrb\n");
	if ((action == RRB || action == RRR) && stacks->b && stacks->b->next)
		rrx(&stacks->b);
	if (action == RRR && verbose &&
			((stacks->a && stacks->a->next) || (stacks->b && stacks->b->next)))
		ft_printf("rrr\n");

	//ft_dprintf(2, "After : diff = %i, nb = %i\n", stacks->diff, stacks->nb);
	//if (verbose)
	//	put_stacks(stacks);
}
