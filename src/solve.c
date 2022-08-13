/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:42:50 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/13 20:55:46 by iel-amra         ###   ########lyon.fr   */
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

void	line_first_step(t_stacks *stacks, int nb, int *line, int best_sa)
{
	int	i;
	int	j;

	i = 0;
	j = line[nb];
	while (j < nb)
	{
		if (best_sa >> i & 1)
			move(stacks, SA, 1);
		if (line[j] == int_content(stacks->a))
		{
			move(stacks, PB, 1);
			j++;
		}
		else if (j < nb)
			move(stacks, RA, 1);
		i++;
	}
}

void	line_prepare_second(t_stacks *stacks, int nb, int *line)
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
}

void	line_second_step(t_stacks *stacks, int nb, int *line)
{
	int	smallest;

	smallest = line[0];
	if (line[nb - 1] < smallest)
		smallest = line [nb - 1];
		if (stacks->b && (!stacks->a || !is_in_tab(line, int_content(stacks->a), nb) || int_content(stacks->b) < int_content(stacks->a)))
				move(stacks, PA, 1);
		move(stacks, RA, 1);
	while (!stacks->a || stacks->b || (is_in_tab(line, int_content(stacks->a), nb) && int_content(stacks->a) != smallest))
	{
		if (stacks->b && (!stacks->a || !is_in_tab(line, int_content(stacks->a), nb) 
				|| int_content(stacks->a) == smallest || int_content(stacks->b) < int_content(stacks->a)))
				move(stacks, PA, 1);
		move(stacks, RA, 1);
	}
}

int	line_solve(t_stacks *stacks, int nb)
{
	int	best_sa;
	int	*line;

	get_best_sa(stacks, nb, &line, &best_sa);
	if (!line)
		return (1);
	//print_tab(line, nb);
	//put_stacks(stacks);
	line_first_step(stacks, nb, line, best_sa);
	//put_stacks(stacks);
	line_prepare_second(stacks, nb, line);
	//put_stacks(stacks);
	line_second_step(stacks, nb, line);
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
	line_solve(stacks, nb_max + 1, line, best_sa);
	return (0);
*/
	
	if (nb_max + 1 < 8)
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
		line_solve(stacks, len_line);
	if ((nb_max + 1) % len_line)
		line_solve(stacks, (nb_max + 1) % len_line);
	return (0);
}
