int	ft_factoriel(int nb)
{
	int	res;

	res = 1;
	while (nb > 1)
	{
		res *= nb;
		nb--;	
	}
	return (res);
}

int	*int_copy(int *nb)
{
	int	*cpy;

	cpy = malloc(sizeof(int));
	if (!cpy)
		return ((void *) 0);
	*cpy = *nb;
	return (cpy);
}

t_stacks	*copy_stacks(t_stacks *stacks)
{
	t_stacks	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return ((void *) 0);
	new->a = ft_lstmap(stacks->a, (void *) int_copy, free);
	if (!new->a && stacks->a)
	{
		free(new);
		return ((void *) 0);
	}
	new->b = ft_lstmap(stacks->b, (void *) int_copy, free);
	if (!new->b && stacks->b )
	{
		ft_lstclear(&new->a, free);
		free(new);
		return ((void *) 0);
	}
	new->nb = stacks->nb;
	return (new);
}

void	free_stacks(t_stacks *stacks)
{
	ft_lstclear(&stacks->a, free);
	ft_lstclear(&stacks->b, free);
	free(stacks);
}

static char	*new_brute(int nb)
{
	char	*brute;
	int	i;

	i = ft_factoriel(nb + 1);
	i *= 3;
	brute = malloc((i + 1) * sizeof(*brute));
	if (!brute)
		return ((void *) 0);
	brute[0] = nb;
	brute[i - 2] = SORTED;
	brute[i - 1] = 0;
	brute[i] = 0;
	i -= 3;
	while (i > 0)
	{ 
		brute[i] = -1;
		i--; 
	} 
	return (brute); 
}

int	brute_recur(char *brute, t_stacks *stacks, int nb, int restricted)
{
	int	i;
	int	ret;
	char	*best_move;
	char	*new_best;


	best_move = get_best_move(stacks, brute);
	if (nb == 0)
		return (try_moves(brute, stacks, best_move[1], restricted));
	i = PA;
	ret = 0;
	while (i <= SS)
	{
		while (i <= SS && forbidden_move(stacks, i, restricted))
			i++;
		move(stacks, i, 0);
		new_best = get_best_move(stacks, brute); 
		if (new_best[1] > best_move[1] && new_best[2] < best_move[2])
		{
			new_best[2] = best_move[2];
			ret += brute_recur(brute, stacks, nb - 1, restricted);
		}
		move(stacks, get_opposite_move(i), 0);
		i++;
	}
	return (ret);
}

char	*brute_force(int nb, int restricted)
{
	char		*brute;
	t_stacks	stacks;
	int		ret;
	int		i;

	brute = new_brute(nb);
	if (!brute)
		return ((void *) 0);
	brute[0] = nb;
	stacks.a = create_stack(nb);
	if (!stacks.a)
	{
		free(brute);
		return ((void *) 0);
	}
	stacks.b = (void *) 0;
	stacks.nb = nb;
	i = 0;
	ret = 1;
	while (ret)
	{
		ret = brute_recur(brute, &stacks, i, restricted);
		brute[ft_factoriel(nb + 1) * 3]++;
		i++;
	}
	ft_lstclear(&stacks.a, free);
	return (brute);
}


int	get_opposite_move(int	i)
{
	if (i < PB)
		return (i + 4);
	if (i < SA)
		return (i - 4);
	return (i);
}

int	forbidden_move(t_stacks *stacks, int action, int restricted)
{
	(void) restricted;
	if (action == PA && !stacks->b)
		return (1);
	if (action == PB && !stacks->a)
		return (1);
	if ((action == SA || action == SB || action == SS) && restricted)
		return (1);
	return (0);
}

int	try_moves(char *brute, t_stacks *stacks, int circle, int restricted)
{
	int		i;
	int		ret;
	char		*best_move;
/*	static int	compt;

	if (compt % 1 == 0)
		ft_printf("Compteur : %i\n", compt);
	compt++;*/
	i = PA;
	ret = 0;
	while (i <= SS)
	{
		while (i <= SS && forbidden_move(stacks, i, restricted))
			i++;
		move(stacks, i, 0);
		best_move = get_best_move(stacks, brute);
		if (*best_move == -1)
		{
			//put_stacks(stacks);
			ret++;
			*best_move = get_opposite_move(i);
			best_move[1] = circle + 1;
		}
		move(stacks, get_opposite_move(i), 0);
		i++;
	}
	return (ret);
}

static int	get_nb_at_pos(t_stacks *stacks, int pos)
{
	t_list	*travel;

	travel = stacks->a;
	if (!travel)
		travel = stacks->b;
	while (pos > 0  && travel)
	{
		travel = travel->next;
		pos--;
	}	
	if (travel == (void *) 0)
		travel = stacks->b;
	while (pos > 0 && travel)
	{
		travel = travel->next;
		pos--;
	}
	if (!travel)
		ft_dprintf(2, "Error get_nb_at_pos\n");
	return (int_content(travel));
}

static int	get_rang(t_stacks *stacks, int pos)
{
	int	rang;
	int	nb;

	t_list	*travel;

	nb = get_nb_at_pos(stacks, pos);
	travel = stacks->a;
	if (!travel)
		travel = stacks->b;
	rang = 0;
	while (pos > 0  && travel)
	{
		if (nb > int_content(travel))
			rang++;
		travel = travel->next;
		pos--;
	}	
	if (travel == (void *) 0)
		travel = stacks->b;
	while (pos > 0 && travel)
	{
		if (nb > int_content(travel))
			rang++;
		travel = travel->next;
		pos--;
	}
	if (!travel)
		ft_dprintf(2, "Error get_rang\n");
	return (rang);
}

char	*get_best_move(t_stacks *stacks, char *brute)
{
	int	i;
	int	nb;

	//put_stacks(stacks);
	nb = brute[0];
	i = 0;
	while (i < nb)
	{
		brute += ft_factoriel(i) * get_rang(stacks, i) * 3;
		i++;
	}
	brute += ft_factoriel(nb) * ft_lstsize(stacks->a) * 3;
	//ft_printf("best : %i\n", brute[1]);
	return (brute + 1);
}
