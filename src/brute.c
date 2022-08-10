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

 /*stiatic t_list	*new_pile(int nb) 
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
}*/

 /*char	*brute_force(int nb, int restricted)
{
	char		*brute;
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
}*/

int	brute_recur(char *brute, t_stacks *stacks, int nb, int restricted)
{
	int	i;
	int	ret;
	char	*best_move;
	char	*new_best;

	best_move = get_best_move(stacks, brute);
	if (nb == 0)
		return (try_moves(brute, stacks, restricted, best_move[1]));
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
	stacks.diff = 0;
	stacks.nb = nb;
	stacks.total = nb;
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
	//ft_printf("In function, action = %i, restricted = %i\n", action, restricted);
	if (action == PA && !stacks->b)
		return (1);
	if (action == PB && !stacks->a)
		return (1);
	if ((action == RA || action == RR) && restricted && stacks->diff == stacks->nb - 1)
		return (1);
	if ((action == RRA || action == RRR) && restricted && stacks->diff == 0)
		return (1);
	if (action == PB && restricted && stacks->nb == 0)
		return (1);
	//ft_printf("returned 0 this time\n");
	return (0);
}

int	try_moves(char *brute, t_stacks *stacks, int restricted, int circle)
{
	int		i;
	int		ret;
	char		*best_move;
	static int	compteur = 0;

	i = PA;
	ret = 0;
	if (compteur % 20000 == 0)
		ft_printf("Circle : %i, compteur : %i\n", circle, compteur);
	compteur++;
	//put_stacks(stacks);
	while (i <= SS)
	{
		//ft_dprintf(2, "Original :\n");
		//put_stacks(stacks);
		while (i <= SS && forbidden_move(stacks, i, restricted))
			i++;
		move(stacks, i, 0);
		best_move = get_best_move(stacks, brute);
		//ft_dprintf(2, "Altered best_move = %i\n", *best_move);
		//put_stacks(stacks);
		if (*best_move == -1)
		{
			ret++;
			*best_move = get_opposite_move(i);
			best_move[1] = circle + 1;
		}
		move(stacks, get_opposite_move(i), 0);
		i++;
	}
	return (ret);
}

 /*int	try_moves(char *brute, t_list *pile, int restricted)
{
	int		i;
	t_stacks	*copy;
	char		*best_move;

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
}*/

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

char	*get_best_move(t_stacks *stacks, char *brute)
{
	int	i;
	int	nb;
	//char	*debug = brute;
	nb = brute[0];
	i = 0;
	while (i < nb)
	{
		brute += ft_factoriel(i) * get_rang(stacks, i) * 3;
		i++;
	}
	brute += ft_factoriel(nb) * stacks->nb * 3;
	//put_stacks(stacks);
	//ft_dprintf(2, "case 12 : %i\n", brute - debug);
	//ft_dprintf(2, "pointeur : %i\n", brute + 1 - debug);
	return (brute + 1);
}
