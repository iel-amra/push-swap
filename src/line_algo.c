void	get_best_sa(t_stacks *stacks, int nb, int **line, int *best_sa)
{
	int	i;
	int	best_score;
	int	score;
	int	*new_line;

	//*best_sa = -1;
	i = 0;
	best_score = -3;
	*line = (void *) 0;
	while (i < ft_pow(2, nb - 1) && (i == 0 || *line))
	{	
		move_sa_binary(stacks, nb, i, 0);
		score = score_line(stacks, nb, &new_line);	
		if ((score > best_score && (true_bits(i) < true_bits(*best_sa) || best_score < 0)) || score == -2)
		{
			free(*line);
			*line = new_line;
			best_score = score;
			*best_sa = i;
		}
		move_sa_binary(stacks, nb, i, 1);
		i++;
	}
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

int	score_line(t_stacks *stacks, int nb, int **line)
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
	score = score_recur(stacks, nb, nb, line);
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

int	score_recur(t_stacks *stacks, int step, int nb, int **line)
{
	int	*new;
	int	i;
	int	score;
	int	score_tab[2];

	if (step == 0)
		return (stop_recur(stacks, line, nb));
	i = 0;
	while ((*line)[i] != -1)
		i++;
	new = tab_int_copy(*line, nb + 1);
	if (!new)
		return (-2);
	new[i] = int_content(stacks->a);
	move(stacks, RA, 0);
	score_tab[0] = -3;
	if ((*line)[0] == -1 || new[i - 1] < new[i])
		score_tab[0] = score_recur(stacks, step - 1, nb, &new);
	score_tab[1] = score_recur(stacks, step - 1, nb, line);
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

int	stop_recur(t_stacks *stacks, int **line, int nb)
{
	int	i;
	int	sep;

	//static int	compteur = 0;

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
/*
	if (score_tab(*line, nb) >= 0) 
	{
		ft_printf("%i\n", compteur);
	   	print_tab(*line, nb);
	}
	compteur++;
*/
	return (score_tab(*line, nb));
}

int	score_tab(int *line, int nb)
{
	int	i;

	i = line[nb];
	while (i < nb - 1)
	{
		if (line[i] < line[i + 1])
			return (-1);
		i++;
	}
	return (line[nb]);
}

int	choose_best_score(int *score, int **line, int **new)
{
	if (score[0] > score[1])
	{
		free(*line);
		*line = *new;
	}
	*new = (void *) 0;
	if (score[1] == -2 || score[0] == -2)
		return (-2);
	if (score[0] > score[1])
		return (score[0]);
	return (score[1]);	
}
