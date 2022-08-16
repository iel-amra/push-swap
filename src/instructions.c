/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:07:44 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:22:00 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//push the first element of stack y to the top of stack x

void	px(t_list **stack_x, t_list **stack_y)
{
	t_list	*tmp;

	if (!*stack_y)
		return ;
	tmp = *stack_y;
	*stack_y = (*stack_y)->next;
	tmp->next = (*stack_x);
	*stack_x = tmp;
}

//switch the two first element of the stack

void	sx(t_list **stack)
{
	t_list	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = (*stack)->next;
	(*stack)->next = (*stack)->next->next;
	tmp->next = (*stack);
	*stack = tmp;
}

void	rx(t_list **stack)
{
	t_list	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	ft_lstlast(*stack)->next = tmp;
	tmp->next = (void *) 0;
}

void	rrx(t_list **stack)
{
	t_list	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	while (tmp->next->next)
		tmp = tmp->next;
	tmp->next->next = *stack;
	*stack = tmp->next;
	tmp->next = (void *) 0;
}
