/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:51:16 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 16:30:23 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (parse(argc, argv))
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	stacks.a = stack_from_argv(argc, argv);
	stacks.b = (void *) 0;
	if (!stacks.a)
		return (1);
	if (is_sorted(&stacks))
	{
		ft_lstclear(&stacks.a, free);
		return (0);
	}
	if (solve(&stacks))
	{
		ft_lstclear(&stacks.a, free);
		ft_lstclear(&stacks.b, free);
		return (1);
	}
	ft_lstclear(&stacks.a, free);
	return (0);
}
