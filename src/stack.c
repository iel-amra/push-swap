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

t_list	*stack_from_argv(int argc, char **argv)
{
	int	i;
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
			ft_dprintf(2, "There are two equal numbers\n");
			return ((void * ) 0);
		}
		travel = travel->next;
		i++;
	}
	return (stack);
}

t_list	*create_stack(int nb)
{
	t_list	*stack;
	t_list	*new;

	stack = (void *) 0;
	nb--;
	while (nb >= 0)
	{
		new = malloc(sizeof(int));
		if (!new || ft_lstadd_front(&stack, ft_lstnew(new)))
		{
			free(new);
			ft_lstclear(&stack, free);
			ft_dprintf(2, "Malloc Error\n");
			return ((void *) 0);	
		}
		*(int *) stack->content = nb;
		nb--;
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
		if (ft_atoi(str) == ft_atoi(argv[i]) && str != argv[i])
			return (-1);
		i--;
	}
	return (nb);
}

int int_content(t_list *stack)
{
	if (!stack)
	{
		ft_dprintf(2, "Error int_content\n");
		return (-1);
	}
	return (*((int *) stack->content));
}
