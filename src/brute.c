/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:53:16 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:24:25 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

static char	*new_brute(int nb)
{
	char	*brute;
	int		i;

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
	int		i;
	int		ret;
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

int	prepare_brute(int nb, char **brute, t_stacks *stacks)
{
	*brute = new_brute(nb);
	if (!*brute)
		return (1);
	(*brute)[0] = nb;
	stacks->a = create_stack(nb);
	if (!stacks->a)
	{
		free(*brute);
		return (1);
	}
	stacks->b = (void *) 0;
	stacks->nb = nb;
	return (0);
}

char	*brute_force(int nb, int restricted)
{
	char		*brute;
	t_stacks	stacks;
	int			ret;
	int			i;

	if (prepare_brute(nb, &brute, &stacks))
		return ((void *) 0);
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
