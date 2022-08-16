/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:05:52 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:09:57 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	get_best_sa(t_stacks *stacks, int nb, int **line, int *best_sa)
{
	int	i;
	int	best_score;
	int	score;
	int	*new_line;

	i = 0;
	best_score = -3;
	*line = (void *) 0;
	while (i < ft_pow(2, nb - 1) && (i == 0 || *line))
	{	
		move_sa_binary(stacks, nb, i, 0);
		score = score_line(stacks, nb, &new_line);
		if ((score > best_score && (true_bits(i) < true_bits(*best_sa)
					|| best_score < 0)) || score == -2)
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
