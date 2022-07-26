/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:35:09 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/23 19:21:02 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

t_list *create_stack(int argc, char **argv)
{
	int		i;
	t_list	*stack;

	stack = (void *) 0;
	i = argc - 1;
	while (i > 0)
	{
		if (ft_lstadd_front(&stack, ft_lstnew(malloc(sizeof(int)))))
		{
			ft_lstclear(&stack, free);
			ft_dprintf(2, "Malloc Error\n");
			return ((void *) 0);	
		}
		int_content(stack) = indice(argv[i], argc - 1, argv);
		if (int_content(stack) == -1)
		{
			ft_lstclear(&stack, free);
			ft_dprintf(2, "There are two equal numbers");
			return ((void * ) 0);
		}
		i--;
	}
	return (stack);
}

int	indice(char *str, int i, char **argv)
{
	int	nb;

	nb = 0;
	while (i > 0)
	{
		if (ft_atoi(str) > ft_atoi(argv[i]))
			nb++;
		if (ft_atoi(str) == ft_atoi(argv[i]))
			return (-1);
		i--;
	}
	return (nb);
}

int int_content(t_lst *stack)
{
	return (*((int) stack);
}
