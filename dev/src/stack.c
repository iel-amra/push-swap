/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:35:09 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:07:40 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

int	int_content(t_list *stack)
{
	if (!stack)
	{
		ft_dprintf(2, "Error int_content\n");
		return (-1);
	}
	return (*((int *) stack->content));
}

t_stacks	*copy_stacks(t_stacks *stacks)
{
	t_stacks	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return ((void *) 0);
	new->a = ft_lstmap(stacks->a, (void *) int_copy, free);
	if (!new->a && stacks->a)
	{
		free(new);
		return ((void *) 0);
	}
	new->b = ft_lstmap(stacks->b, (void *) int_copy, free);
	if (!new->b && stacks->b)
	{
		ft_lstclear(&new->a, free);
		free(new);
		return ((void *) 0);
	}
	new->nb = stacks->nb;
	return (new);
}

void	free_stacks(t_stacks *stacks)
{
	ft_lstclear(&stacks->a, free);
	ft_lstclear(&stacks->b, free);
	free(stacks);
}
