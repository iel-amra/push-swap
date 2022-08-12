void	get_best_sa(t_stacks *stacks, int nb, int **line, char *best_sa)
{
	char	i;
	int	best_score;
	int	score;
	int	*new_line;

	*best_sa = 0;
	i = 0;
	best_score = -3;
	while (i < ft_pow(2, nb - 1) && (i == 0 || line))
	{
		move_sa_byte(stacks, nb, i, 0);
		score = score_line(stacks, nb, &new_line);
		if (score > best_score || score == -2)
		{
			free(*line);
			*line = new_line;
			best_score = score;
			*best_sa = i;
		}
		free(new_line);
		move_sa_byte(stacks, nb, i, 1);
		i++;
	}
}

void	move_sa_byte(t_stacks *stacks, int nb, char byte, int mode)
{
	char	i;

	i = 0;
	while (i < nb - 1)
	{
		if (byte >> i & 1 && mode == 0)
			move(stacks, SA, 0);
		move(stacks, RA, 0);
		i++;
	}
	while (i > 0)
	{
		if (byte >> i & 1 && mode == 1)
			move(stacks, SA, 0);
		move(stacks, RRA, 0);
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
		*line = (void *);
	}
	return (score);
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
	(*new)[i] = int_content(stacks->a);
	move(stacks, RA);
	score_tab[0] = -3;
	if (!*line[0] == -1 || (*line)[i] < (*new)[i])
		score_tab[0] = score_recur(stacks, step - 1, nb, new);
	score_tab[1] = score_recur(stacks, step - 1, nb, line);
	move(stacks, RRA);
	score = choose_best_score(score_tab, line, &new);
	return (score);
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
