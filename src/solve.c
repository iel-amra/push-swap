/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:42:50 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/14 18:27:31 by iel-amra         ###   ########lyon.fr   */
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

void	line_first_step(t_stacks *stacks, int *data, int *line, int best_sa)
{
	int	i;
	int	j;

	i = 0;
	j = line[data[0]];
	while (j < data[0] || best_sa >> i)
	{
		if (best_sa >> i & 1)
			move(stacks, SA, data[1]);
		i++;
		if (j < data[0] && line[j] == int_content(stacks->a))
		{
			move(stacks, PB, data[1]);
			j++;
		}
		else if (j < data[0] || best_sa >> i)
			move(stacks, RA, data[1]);
	}
}

int	prep_second_step(t_stacks *stacks, int *data, int *line)
{
	int	i;
	int	moved;
	
	moved = 0;
	i = line[data[0]];
	if (i >= data[0] - 1 || line[i] > line[i + 1])
		return (moved);
	while (int_content(stacks->b) > int_content(stacks->a) && is_in_tab(line, int_content(stacks->a), i) && (int_content(stacks->a) != line[0] || !moved))
	{
		move(stacks, RA, data[1]);
		moved = 1;
	}
	return ((moved && int_content(stacks->a) == line[0]) + (!moved && int_content(stacks->a) == line[0]) * -1 );
}

void	line_second(t_stacks *stacks, int *data, int *line, int moved)
{
	int	sep;
	int last;

	sep = line[data[0]];
	if (sep == data[0])
		return ;
	last = int_content(ft_lstlast(stacks->a));
	if ((moved == 1 || !is_in_tab(line, int_content(stacks->a), sep)) && stacks->b && last < int_content(stacks->b))
	{
		moved = 0;
		move(stacks, PA, data[1]);
	}
	while (stacks->b && moved != 1 && int_content(stacks->a) > int_content(stacks->b) && (moved == -1 || last < int_content(stacks->b)))
		move(stacks, PA, data[1]);
	while (moved != -1 && is_in_tab(line, last, sep) && stacks->b && last > int_content(stacks->b))
	{
		if (int_content(stacks->a) == line[0] && moved == 0)
			moved = -1;
		moved = 0;
		move(stacks, RRA, data[1]);
		last = int_content(ft_lstlast(stacks->a));
		while (stacks->b && int_content(stacks->a) > int_content(stacks->b) && (int_content(stacks->a) <= line[0] || last < int_content(stacks->b)))
			move(stacks, PA, data[1]);
	}
}
/*
 void	line_second(t_stacks *stacks, int nb, int *line)
{
	int	sep;
	int last;

	sep = line[nb];
	if (sep == nb)
		return ;
	last = int_content(ft_lstlast(stacks->a));
	while (is_in_tab(line, last, sep) && last > line[nb - 1] && int_content(stacks->a) != line[0])
	{
		move(stacks, RRA, 1);
		last = int_content(ft_lstlast(stacks->a));
	}
}*/

int	get_smallest(int *tab, int nb)
{
	int smallest;
	int i;

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

void	line_third_step(t_stacks *stacks, int *data, int *line)
{
	int	smallest;

	smallest = get_smallest(line, data[0]);
	if (stacks->b && (!stacks->a || !is_in_tab(line, int_content(stacks->a), data[0]) || int_content(stacks->b) < int_content(stacks->a)))
		move(stacks, PA, data[1]);
	move(stacks, RA, data[1]);
	while (!stacks->a || stacks->b || (is_in_tab(line, int_content(stacks->a), data[0]) && int_content(stacks->a) != smallest))
	{
		if (stacks->b && (!stacks->a || !is_in_tab(line, int_content(stacks->a), data[0]) 
				|| int_content(stacks->a) == smallest || int_content(stacks->b) < int_content(stacks->a)))
				move(stacks, PA, data[1]);
		move(stacks, RA, data[1]);
	}
}

int	best_line_solve(t_stacks *stacks, int nb)
{
	int			ret;
	int 		i;
	int			j;
	t_stacks	*copy;

	ret = line_solve(stacks, nb, 1);

	if (ret >= 0)
		return (ret);
	i = 2;
	while (ret == -1)
	{
		copy = copy_stacks(stacks);
		if (!copy)
			return (1);
		if (line_solve(copy, i, 0) == 0)
		{
			j = 0;
			while (j++ < i)
				move(copy, RRA, 0);
			ret = line_solve(copy, nb, 0);
		}
		free_stacks(copy);
		i++;
	}
	i--;
	//ft_dprintf(2, "Found : %i\n", i);
	if (line_solve(stacks, i, 1))
		return (1);
	j = 0;
	while (j++ < i)
		move(stacks, RRA, 1);
	if (line_solve(stacks, nb, 1))
		return (1);
	return (0);
}

int	line_solve(t_stacks *stacks, int nb, int verbose)
{
	int	best_sa;
	int	*line;
	int	moved;
	int	data[2];

	data[0] = nb;
	data[1] = verbose;
	get_best_sa(stacks, nb, &line, &best_sa);
	if (!line)
		return (1);

	/*
	move_sa_binary(stacks, nb, best_sa, 0);
	if (score_line(stacks, nb, &line) == -1)
	{
		move_sa_binary(stacks, nb, best_sa, 1);
		int i = 0;
		line_solve(stacks, nb - 4);
		while (i++ < nb - 4)
			move(stacks, RRA, 1);
	}
	else
		move_sa_binary(stacks, nb, best_sa, 1);
	*/

	move_sa_binary(stacks, nb, best_sa, 0);
	if (score_line(stacks, nb, &line) == -1)
	{
		move_sa_binary(stacks, nb, best_sa, 1);
		return (-1);
	}
	else
		move_sa_binary(stacks, nb, best_sa, 1);

	get_best_sa(stacks, nb, &line, &best_sa);
	move_sa_binary(stacks, nb, best_sa, 0);
	if (score_line(stacks, nb, &line) == -1)
	{
		ft_dprintf(2, "Nothing found 2\n");
		move_sa_binary(stacks, nb, best_sa, 1);
		//put_stacks(stacks);
		return (1);
	}
	move_sa_binary(stacks, nb, best_sa, 1);
	if (!line)
		return (1);


	//print_tab(line, nb);
	//put_stacks(stacks);
	line_first_step(stacks, data, line, best_sa);
	//put_stacks(stacks);
	moved = prep_second_step(stacks, data, line);
	//put_stacks(stacks);
	line_second(stacks, data, line, moved);
	//put_stacks(stacks);
	line_third_step(stacks, data, line);
	//put_stacks(stacks);
	free(line);
	return (0);
}

int	solve(t_stacks *stacks)
{
	int	nb_bit_max;
	int	i;
	int	nb_max;
	char	*brute;
	int	nb_line;
	int	len_line;	

	nb_max = get_nb_max(stacks->a);
	nb_bit_max = get_nb_bit(nb_max);
	
/*
	line_solve(stacks, nb_max + 1);
	return (0);
*/
	
	if (nb_max + 1 < 7)
	{
		brute = brute_force(nb_max + 1, 0);
		if (!brute)
			return (1);
		stacks->nb = nb_max + 1;
		char best_move = *get_best_move(stacks, brute);
		while (best_move != SORTED)
		{
			move(stacks, best_move, 1);
			best_move = *get_best_move(stacks, brute);
		}
		free(brute);
		return (0);
	}

	i = nb_bit_max % 4;
	while (i < nb_bit_max)
	{
		radix(i, stacks, nb_max + 1, A_TO_B);
		radix(i + 2, stacks, nb_max + 1,
			B_TO_A | LAST * (i + 4 >= nb_bit_max));	
		i += 4;
	}
	len_line = ft_pow(2, nb_bit_max % 4);
	nb_line = (nb_max + 1) / len_line; 
	i = 0;
	while (i++ < nb_line)
		best_line_solve(stacks, len_line);
	if ((nb_max + 1) % len_line)
		best_line_solve(stacks, (nb_max + 1) % len_line);
	return (0);
}
