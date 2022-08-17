/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:24:03 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/17 10:24:08 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
