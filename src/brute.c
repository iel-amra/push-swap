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
	new->diff = stacks->diff;
	new->total = stacks->total;
	return (new);
}

void	free_stacks(t_stacks *stacks)
{
	ft_lstclear(&stacks->a, free);
	ft_lstclear(&stacks->b, free);
	free(stacks);
}

static int	*new_brute(int nb)
{
	int	*brute;
	int	i;

	i = ft_factoriel(nb + 1);
	brute = malloc((i + 1) * sizeof(int));
	if (!brute)
		return ((void *) 0);
	brute[0] = nb;
	brute[i] = SORTED;
	i--;
	while (i > 0)
	{ 
		brute[i] = -1;
		i--; 
	} 
	return (brute); 
}

static t_list	*new_pile(int nb) 
{
       	t_list		*pile;
	t_stacks	*stacks;

	stacks = malloc(sizeof(t_stacks));
	if (!stacks)
		return ((void *) 0);
	pile = (void *) 0;
	ft_lstadd_front(&pile, ft_lstnew(stacks));
	if (!pile)
	{
		free(stacks);
		return ((void *) 0);
	}
	stacks->a = create_stack(nb);
	if (!stacks->a)
	{
		free(stacks);
		free(pile);
		return ((void *) 0);
	}
	stacks->b = (void *) 0;
	stacks->diff = 0;
	stacks->nb = nb;
	stacks->total = nb;
	return (pile);
}

int	*brute_force(int nb, int restricted)
{
	int		*brute;
	t_list		*pile;
	t_list		*tmp;

	//ft_dprintf(2, "NB du brute_force : %i \n", nb);
	pile = new_pile(nb);
	brute = new_brute(nb);
	if (!pile || !brute)
	{
		free(brute);
		ft_lstclear(&pile, (void *) free_stacks);
		return ((void *) 0);
	}
	brute[0] = nb;
	int compteur = 0;
	while (pile)
	{
		if (compteur % 20000 == 0)
			ft_printf("compteur : %i\n", compteur);
		compteur++;
		//ft_dprintf(2, "Nouveau passage\n");
		//ft_lstiter(pile, put_stacks);
		if (try_moves(brute, pile, restricted))
		{
			ft_lstclear(&pile, (void *) free_stacks);
			free(brute);
			return (0);
		}
		tmp = pile;
		pile = pile->next;
		ft_lstdelone(tmp, (void *) free_stacks);
	}
	ft_printf("compteur : %i\n", compteur);
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
	ft_printf("In function, action = %i, restricted = %i\n", action, restricted);
	if (action == PA /*&& !stacks->b*/)
		return (1);
	if (action == PB /*&& !stacks->a*/)
		return (1);
	if ((action == RA || action == RR) && restricted && stacks->diff == stacks->nb - 1)
		return (1);
	if ((action == RRA || action == RRR) && restricted && stacks->diff == 0)
		return (1);
	if (action == PB && restricted && stacks->nb == 0)
		return (1);
	ft_printf("returned 0 this time\n");
	return (0);
}
int	try_moves(int *brute, t_list *pile, int restricted)
{
	int		i;
	t_stacks	*copy;
	int		*best_move;

	i = PA;
	while (i <= SS)
	{
		//ft_dprintf(2, "Original :\n");
		//put_stacks(pile->content);
		while (i <= SS && forbidden_move(pile->content, i, restricted))
			i++;
		move(pile->content, i, 0);
		best_move = get_best_move(pile->content, brute);
		//ft_dprintf(2, "Altered best_move = %i\n", *best_move);
		//put_stacks(pile->content);
		if (*best_move == -1)
		{
			//ft_printf("Entered\n");
			copy = copy_stacks(pile->content);
			if (!copy)
				return (1);
			if (ft_lstadd_back(&pile, ft_lstnew(copy)))
			{
				free_stacks(copy);
				return (1);
			}
			*best_move = get_opposite_move(i);
		}
		move(pile->content, get_opposite_move(i), 0);
		i++;
	}
	return (0);
}

static int	get_nb_at_pos(t_stacks *stacks, int pos)
{
	t_list	*travel;
	int	diff;

	//put_stacks(stacks);
	travel = stacks->a;
	if (!travel)
		travel = stacks->b;
	diff = stacks->diff;
	//ft_dprintf(2, "pos : %i\n", pos);
	while (pos > 0 && diff < stacks->nb && travel) // IL FAUT fouiller le bas de la pile A
	{
		//ft_dprintf(2, "In A, diff : %i, stacks->nb : %i\n", diff, stacks->nb);
		diff++;
		travel = travel->next;
		pos--;
	}
	//ft_dprintf(2, "Mid prev soustraction : %i\n", stacks->total);
	if (diff == stacks->nb)
		travel = ft_lstget(stacks->a, stacks->total - stacks->diff);
	//ft_dprintf(2, "Mid\n");
	while (pos > 0 && travel)
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
	//ft_dprintf(2, "Je retourne : %i\n\n", int_content(travel));
	return (int_content(travel));
}

static int	get_rang(t_stacks *stacks, int pos)
{
	int	rang;
	int	nb;
	
	int	diff;
	t_list	*travel;

	nb = get_nb_at_pos(stacks, pos);
	travel = stacks->a;
	if (!travel)
		travel = stacks->b;
	diff = stacks->diff;
	rang = 0;
	while (pos > 0 && diff < stacks->nb && travel) // IL FAUT fouiller le bas de la pile A
	{
		if (nb > int_content(travel))
			rang++;
		diff++;
		travel = travel->next;
		pos--;
	}
	if (diff == stacks->nb)
		travel = ft_lstget(stacks->a, stacks->total - stacks->diff);
	while (pos > 0 && travel)
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

int	*get_best_move(t_stacks *stacks, int *brute)
{
	int	i;
	int	nb;
	//int	*debug = brute;
	nb = brute[0];
	i = 0;
	while (i < nb)
	{
		brute += ft_factoriel(i) * get_rang(stacks, i);
		i++;
	}
	brute += ft_factoriel(nb) * stacks->nb;
	//put_stacks(stacks);
	//ft_dprintf(2, "pointeur : %i\n", brute + 1 - debug);
	return (brute + 1);
}
