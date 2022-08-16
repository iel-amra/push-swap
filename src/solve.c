/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:42:50 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/16 15:00:16 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int nb, int exp)
{
	int	res;

	res = 1;
	while (exp-- > 0)
		res *= nb;
	return (res);
}

static int	get_nb_bit(int nb)
{
	int	n_bit;

	if (nb == 0)
		return (1);
	n_bit = 0;
	while (nb > 0)
	{
		n_bit++;
		nb /= 2;
	}
	return (n_bit);
}

static int	get_nb_max(t_list *stack)
{
	int	nb_max;
	int	nb;

	nb_max = 0;
	while (stack)
	{
		nb = int_content(stack);
		if (nb > nb_max)
			nb_max = nb;
		stack = stack->next;
	}
	return (nb_max);
}	

int	line_first_step(t_stacks *stacks, int *data, int *line, int best_sa)
{
	int	i;
	int	j;
	int	coups;

	coups = 0;
	i = 0;
	j = line[data[0]];
	while (j < data[0] || best_sa >> i)
	{
		if (best_sa >> i & 1)
			coups += move(stacks, SA, data[1]);
		i++;
		if (j < data[0] && line[j] == int_content(stacks->a))
		{
			coups += move(stacks, PB, data[1]);
			j++;
		}
		else if (j < data[0] || best_sa >> i)
			coups+= move(stacks, RA, data[1]);
	}
	return (coups);
}

int	prep_second_step(t_stacks *stacks, int *data, int *line, int *moved)
{
	int	i;
	int	coups;

	coups = 0;
	*moved = 0;
	i = line[data[0]];
	if (i >= data[0] - 1 || line[i] > line[i + 1])
		return (*moved);
	while (int_content(stacks->b) > int_content(stacks->a)
		&& is_in_tab(line, int_content(stacks->a), i)
		&& (int_content(stacks->a) != line[0] || !*moved))
	{
		coups += move(stacks, RA, data[1]);
		*moved = 1;
	}
	*moved = (*moved && int_content(stacks->a) == line[0])
		+ (!*moved && int_content(stacks->a) == line[0]) * -1;
	return (coups);
}

int	move_downward(t_stacks *stacks, int verbose, int *line, int *moved)
{
	int	last;
	int	coups;

	coups = 0;
	if (int_content(stacks->a) == line[0] && *moved == 0)
		*moved = -1;
	*moved = 0;
	coups += move(stacks, RRA, verbose);
	last = int_content(ft_lstlast(stacks->a));
	while (stacks->b && int_content(stacks->a) > int_content(stacks->b)
		&& (int_content(stacks->a) <= line[0]
			|| last < int_content(stacks->b)))
		coups += move(stacks, PA, verbose);
	return (coups);
}

int	line_second(t_stacks *stacks, int *data, int *line, int moved)
{
	int	sep;
	int	last;
	int	coups;

	coups = 0;
	sep = line[data[0]];
	if (sep == data[0])
		return (coups);
	last = int_content(ft_lstlast(stacks->a));
	if ((moved == 1 || !is_in_tab(line, int_content(stacks->a), sep))
		&& stacks->b && last < int_content(stacks->b))
	{
		moved = 0;
		coups += move(stacks, PA, data[1]);
	}
	while (stacks->b && moved != 1
		&& int_content(stacks->a) > int_content(stacks->b)
		&& (moved == -1 || last < int_content(stacks->b)))
		coups +=move(stacks, PA, data[1]);
	while (moved != -1 && is_in_tab(line, last, sep)
		&& stacks->b && last > int_content(stacks->b))
	{
		coups += move_downward(stacks, data[1], line, &moved);
		last = int_content(ft_lstlast(stacks->a));
	}
	return (coups);
}

int	get_smallest(int *tab, int nb)
{
	int	smallest;
	int	i;

	smallest = tab[0];
	i = 1;
	while (i < nb)
	{
		if (tab[i] < smallest)
			smallest = tab[i];
		i++;
	}
	return (smallest);
}

int	line_third_step(t_stacks *stacks, int *data, int *line)
{
	int	smallest;
	int	coups;

	coups = 0;
	smallest = get_smallest(line, data[0]);
	if (stacks->b && (!stacks->a 
				|| !is_in_tab(line, int_content(stacks->a), data[0])
				|| int_content(stacks->b) < int_content(stacks->a)))
		coups += move(stacks, PA, data[1]);
	coups += move(stacks, RA, data[1]);
	while (!stacks->a || stacks->b 
			|| (is_in_tab(line, int_content(stacks->a), data[0]) 
				&& int_content(stacks->a) != smallest))
	{
		if (stacks->b && (!stacks->a || !is_in_tab(line, int_content(stacks->a), data[0]) 
			|| int_content(stacks->a) == smallest 
			|| int_content(stacks->b) < int_content(stacks->a)))
				coups += move(stacks, PA, data[1]);
		coups += move(stacks, RA, data[1]);
	}
	return (coups);
}

int	get_best_correc(t_stacks *stacks, int nb)
{
	int 		i;
	int			j;
	t_stacks	*copy;
	int			ret;


	i = 2;
	ret = -1;
	while (ret == -1)
	{
		copy = copy_stacks(stacks);
		if (!copy)
			return (1);
		if (line_solve(copy, i, 0) >= 0)
		{
			//ft_dprintf(2, "HERE\n");
			j = 0;
			while (j++ < i)
				move(copy, RRA, 0);
			ret = line_solve(copy, nb, 0);
			//put_stacks(copy);
		}
		//ft_dprintf(2, "score : %i, i = %i\n", ret, i);
		free_stacks(copy);
		i++;
	}
	i--;
	return (i);
}

int	best_line_solve(t_stacks *stacks, int nb)
{
	int			ret;
	int 		correc;
	int			i;

	ret = line_solve(stacks, nb, 1);
	if (ret >= 0)
		return (ret);
	correc = get_best_correc(stacks, nb);
	if (line_solve(stacks, correc, 1) == -2)
		return (1);
	i = 0;
	while (i++ < correc)
		move(stacks, RRA, 1);
	if (line_solve(stacks, nb, 1) == -2)
		return (1);
	return (0);
}

int	line_solve_params(t_stacks *stacks, int *data, int *line, int best_sa)
{
	int	coups;
	int	moved;

	coups = 0;
	/*
	if (data[1])
	{
		ft_dprintf(2, "Begin : \n");
		print_tab(line, data[0]);
		ft_dprintf(2, "\n");
		put_stacks(stacks);
	}
	*/
	coups += line_first_step(stacks, data, line, best_sa);
	coups += prep_second_step(stacks, data, line, &moved);
	coups += line_second(stacks, data, line, moved);
	coups += line_third_step(stacks, data, line);
	return (coups);
}

int	line_solve(t_stacks *stacks, int nb, int verbose)
{
	int	best_sa;
	int	*line;
	int	data[2];
	int	moved;
	int	coups;

	coups = 0;
	(void) coups;
	(void) moved;
	data[0] = nb;
	data[1] = verbose;
	get_best_sa(stacks, nb, &line, &best_sa);
	free(line);
	/*
	move_sa_binary(stacks, nb, best_sa, 0);
	if (score_line(stacks, nb, &line, best_sa) == -1)
	{
		move_sa_binary(stacks, nb, best_sa, 1);
		free(line);
		return (1);
	}
	move_sa_binary(stacks, nb, best_sa, 1);
	*/
	move_sa_binary(stacks, nb, best_sa, 0);
	if (score_line(stacks, nb, &line, best_sa) == 1000)
	{
		move_sa_binary(stacks, nb, best_sa, 1);
		free(line);
		//ft_dprintf(2, "HERE\n");
		return (-1);
	}
	move_sa_binary(stacks, nb, best_sa, 1);

	line_solve_params(stacks, data, line, best_sa);
	/*
	coups += line_first_step(stacks, data, line, best_sa);
	coups += prep_second_step(stacks, data, line, &moved);
	coups += line_second(stacks, data, line, moved);
	coups += line_third_step(stacks, data, line);
	*/
	free(line);
	return (0);
}

int solve_brute(t_stacks *stacks, int nb)
{
	char	best_move;
	char	*brute;

	brute = brute_force(nb, 0);
	if (!brute)
		return (1);
	stacks->nb = nb;
	best_move = *get_best_move(stacks, brute);
	while (best_move != SORTED)
	{
		move(stacks, best_move, 1);
		best_move = *get_best_move(stacks, brute);
	}
	free(brute);
	return (0);
}

int	solve(t_stacks *stacks)
{
	int	nb_bit_max;
	int	i;
	int	nb_max;
	int	nb_line;
	int	len_line;	

	nb_max = get_nb_max(stacks->a) + 1;
	nb_bit_max = get_nb_bit(nb_max - 1);	
	if (nb_max < 8)
		return (solve_brute(stacks, nb_max));
	i = nb_bit_max % 4;
	while (i < nb_bit_max)
	{
		radix(i, stacks, nb_max, A_TO_B);
		radix(i + 2, stacks, nb_max, B_TO_A | LAST * (i + 4 >= nb_bit_max));	
		i += 4;
	}
	len_line = ft_pow(2, nb_bit_max % 4);
	nb_line = nb_max / len_line; 
	i = 0;
	while (i++ < nb_line)
		best_line_solve(stacks, len_line);
	if (nb_max % len_line && best_line_solve(stacks, nb_max % len_line))
			return (1);
	return (0);
}
