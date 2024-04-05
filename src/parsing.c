/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:36:39 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 16:35:00 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	is_sorted(t_stacks *stacks)
{
	t_list	*travel;

	if (stacks->b)
		return (0);
	travel = stacks->a;
	while (travel && travel->next)
	{
		if (int_content(travel) > int_content(travel->next))
			return (0);
		travel = travel->next;
	}
	return (1);
}

int	fit_in_int(char *str)
{
	if (ft_strlen(str) > nb_digit(INT_MAX) && *str != '-')
		return (0);
	if (ft_strlen(str) - 1 > nb_digit(-INT_MAX) && *str == '-')
		return (0);
	if (ft_strlen(str) < nb_digit(INT_MAX) && *str != '-')
		return (1);
	if (ft_strlen(str) - 1 < nb_digit(INT_MIN) && *str == '-')
		return (1);
	if (*str != '-' && overflow(str, INT_MAX, nb_digit(INT_MAX) - 1) == 1)
		return (0);
	if (*str == '-' && overflow(str + 1, -INT_MAX, nb_digit(INT_MIN) - 1) == 1)
		return (0);
	return (1);
}

int	parse(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 1)
		return (0);
	i = 1;
	while (i < argc)
	{
		if ((!ft_isdigit(argv[i][0]) && argv[i][0] != '-')
			|| (argv[i][0] == '-' && argv[i][1] == '\0'))
			return (1);
		j = 1;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		if (!fit_in_int(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	indice(char *str, int i, char **argv)
{
	int	nb;

	nb = 0;
	while (i > 0)
	{
		if (ft_atoi(str) > ft_atoi(argv[i]))
			nb++;
		if (ft_atoi(str) == ft_atoi(argv[i]) && str != argv[i])
			return (-1);
		i--;
	}
	return (nb);
}

t_list	*stack_from_argv(int argc, char **argv)
{
	int		i;
	t_list	*stack;
	t_list	*travel;

	stack = create_stack(argc - 1);
	travel = stack;
	i = 1;
	while (i < argc)
	{	
		*(int *) travel->content = indice(argv[i], argc - 1, argv);
		if (int_content(travel) == -1)
		{
			ft_lstclear(&stack, free);
			ft_dprintf(2, "Error\n");
			return ((void *) 0);
		}
		travel = travel->next;
		i++;
	}
	return (stack);
}
