/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:06:02 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/17 10:55:10 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
	stacks->nb = nb;
	score = score_recur(stacks, nb, line, sa);
	if (score == -2)
	{
		free(*line);
		*line = (void *) 0;
	}
	return (score);
}

int	score_recur(t_stacks *stacks, int step, int **line, int sa)
{
	int	*new;
	int	i;
	int	score;
	int	score_tab[2];

	if (step == 0)
		return (stop_recur(stacks, line, stacks->nb, sa));
	i = 0;
	while ((*line)[i] != -1)
		i++;
	new = tab_int_copy(*line, stacks->nb + 1);
	if (!new)
		return (-2);
	new[i] = int_content(stacks->a);
	move(stacks, RA, 0);
	score_tab[0] = 1000;
	if ((*line)[0] == -1 || new[i - 1] < new[i])
		score_tab[0] = score_recur(stacks, step - 1, &new, sa);
	score_tab[1] = score_recur(stacks, step - 1, line, sa);
	move(stacks, RRA, 0);
	score = choose_best_score(score_tab, line, &new);
	return (score);
}

int	calcul_score(t_stacks *stacks, int **line, int nb, int sa)
{
	t_stacks	*copy;
	int			score;
	int			i;

	copy = copy_stacks(stacks);
	if (!copy)
		return (-2);
	i = 0;
	while (i++ < nb)
		move(copy, RRA, 0);
	move_sa_binary(copy, nb, sa, 1);
	score = line_solve_params(copy, 0, *line, sa);
	free_stacks(copy);
	return (score);
}

int	stop_recur(t_stacks *stacks, int **line, int nb, int sa)
{
	int	i;
	int	sep;

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
	if (score_tab(*line, nb) == -1 || (*line)[nb] == 0)
		return (1000);
	return (calcul_score(stacks, line, nb, sa));
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
