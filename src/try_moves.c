/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:52:34 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:08:35 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
	int			i;
	int			ret;
	char		*best_move;

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
	return (int_content(travel));
}

static int	get_rang(t_stacks *stacks, int pos)
{
	int		rang;
	int		nb;
	t_list	*travel;

	nb = get_nb_at_pos(stacks, pos);
	travel = stacks->a;
	if (!travel)
		travel = stacks->b;
	rang = 0;
	while (pos-- > 0 && travel)
	{
		if (nb > int_content(travel))
			rang++;
		travel = travel->next;
	}	
	if (travel == (void *) 0)
		travel = stacks->b;
	while (pos-- > 0 && travel)
	{
		if (nb > int_content(travel))
			rang++;
		travel = travel->next;
	}
	return (rang);
}

char	*get_best_move(t_stacks *stacks, char *brute)
{
	int	i;
	int	nb;

	nb = brute[0];
	i = 0;
	while (i < nb)
	{
		brute += ft_factoriel(i) * get_rang(stacks, i) * 3;
		i++;
	}
	brute += ft_factoriel(nb) * ft_lstsize(stacks->a) * 3;
	return (brute + 1);
}
