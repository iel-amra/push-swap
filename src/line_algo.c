void	get_best_sa(t_stacks *stacks, int nb, int **line, int *best_sa)
{
	int	i;
	int	best_score;
	int	score;
	int	*new_line;

	i = 0;
	best_score = 1000;
	*line = (void *) 0;
	while (i < ft_pow(2, nb - 1) && (i == 0 || *line))
	{	
		move_sa_binary(stacks, nb, i, 0);
		score = score_line(stacks, nb, &new_line, i);	
		if (score < best_score || score == -2)
		{
			free(*line);
			*line = new_line;
			new_line = (void *) 0;
			best_score = score;
			*best_sa = i;
		}
		free(new_line);
		move_sa_binary(stacks, nb, i, 1);
		i++;
	}
	//ft_dprintf(2, "TEST : %i\n", best_score);

}

int	true_bits(int x)
{
	unsigned long	i;
	int	nb;

	nb = 0;
	i = 0;
	while (i < sizeof(int))
	{
		if (x >> i & 1)
			nb++;
		i++;
	}
	return (nb);
}

void	move_sa_binary(t_stacks *stacks, int nb, int byte, int mode)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (byte >> i & 1 && mode == 0)
			move(stacks, SA, 0);
		move(stacks, RA, 0);
		i++;
	}
	i--;
	while (i >= 0)
	{
		move(stacks, RRA, 0);
		if (byte >> i & 1 && mode == 1)
			move(stacks, SA, 0);
		i--;
	}
}

int	score_line(t_stacks *stacks, int nb, int **line, int sa)
{
	int	i;
	int	score;

	*line = malloc((nb + 1) * sizeof(**line));
	if (!*line)
		return (-2);
	i = 0;
	while (i < nb + 1)
	{
		(*line)[i] = -1;
		i++;
	}
	score = score_recur(stacks, nb, nb, line, sa);
	if (score == -2)
	{
		free(*line);
		*line = (void *) 0;
	}
	return (score);
}

int	*tab_int_copy(int *line, int len)
{
	int	*cpy;

	cpy = malloc(len * sizeof(int));
	if (!cpy)
		return ((void *) 0);
	while (--len >= 0)
		cpy[len] = line[len];
	return (cpy);
}

int	score_recur(t_stacks *stacks, int step, int nb, int **line, int sa)
{
	int	*new;
	int	i;
	int	score;
	int	score_tab[2];

	if (step == 0)
		return (stop_recur(stacks, line, nb, sa));
	i = 0;
	while ((*line)[i] != -1)
		i++;
	new = tab_int_copy(*line, nb + 1);
	if (!new)
		return (-2);
	new[i] = int_content(stacks->a);
	move(stacks, RA, 0);
	score_tab[0] = 1000;
	if ((*line)[0] == -1 || new[i - 1] < new[i])
		score_tab[0] = score_recur(stacks, step - 1, nb, &new, sa);
	score_tab[1] = score_recur(stacks, step - 1, nb, line, sa);
	move(stacks, RRA, 0);
	score = choose_best_score(score_tab, line, &new);
	return (score);
}

int	is_in_tab(int *tab, int nb, int len)
{
	while (len-- > 0)
	{
		if (*tab++ == nb)
			return (1);
	}
	return (0);
}

void	print_tab(int *tab, int nb)
{
	int	i = 0;

	while (i < nb)
	{
		ft_printf("%i ", tab[i]);
		i++;
	}
	ft_printf("\n");
}

int	stop_recur(t_stacks *stacks, int **line, int nb, int sa)
{
	int	i;
	int	sep;
	int	score;
	(void) score;
	(void) sa;
	//static int	compteur = 0;

	//ft_printf("%i\n", compteur);

	i = 0;
	while (i++ < nb)
		move(stacks, RRA, 0);
	sep = 0;
	while ((*line)[sep] != -1)
		sep++;
	(*line)[nb] = sep;
	i = 0;
	while (i++ < nb)
	{
		if (!is_in_tab(*line, int_content(stacks->a), nb))
			(*line)[sep++] = int_content(stacks->a);
		move(stacks, RA, 0);
	}
	if (score_tab(*line, nb) == -1)
		return (1000);
	t_stacks *copy = copy_stacks(stacks); //proteger !
	i = 0;
	while (i++ < nb)
		 move(copy, RRA, 0);
	move_sa_binary(copy, nb, sa, 1);
	//ft_dprintf(2, "%p\n", stacks);
	score = line_solve_params(copy, (int[]){nb, 0}, *line, sa);
	/*
	if (score_tab(*line, nb) >= 0) 
	{
		ft_printf("%i Sep : %i\n", compteur, (*line)[nb]);
	   	print_tab(*line, nb);
	}
	compteur++;
	*/
	free_stacks(copy);
	//ft_dprintf(2, "score middle : %i\n", score);
	//return (score_tab(*line, nb));
	return (score);
}

int	score_tab(int *line, int nb)
{
	int	i;
	int	pivot;

	pivot = 1;
	i = line[nb];
	if (i < nb - 1 && line[i] < line[i + 1])
			pivot = -1;
	i++;
	while (i < nb - 1)
	{
		if (line[i] * pivot < line[i + 1] * pivot)
			return (-1);
		i++;
	}
	return (line[nb]);
}

int	choose_best_score(int *score, int **line, int **new)
{
	if (score[0] < score[1])
	{
		free(*line);
		*line = *new;
	}
	else
		free(*new);
	*new = (void *) 0;
	if (score[1] == -2 || score[0] == -2)
		return (-2);
	if (score[0] < score[1])
		return (score[0]);
	return (score[1]);	
}