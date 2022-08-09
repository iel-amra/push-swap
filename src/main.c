/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:51:16 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/23 18:57:53 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	p_putnbr(void *nb)
{
	ft_printf("%i\n", *(int *)nb);
}

void	put_stacks(void *src)
{
	t_stacks	stacks;

	stacks = *(t_stacks *)src;
	while (stacks.a || stacks.b)
	{
		if (stacks.a)
		{
			ft_printf("%i     ", int_content(stacks.a));
			stacks.a = stacks.a->next;
		}
		else
			ft_printf("      ");
		if (stacks.b)
		{
			ft_printf("%i\n", int_content(stacks.b));
			stacks.b = stacks.b->next;
		}
		else
			ft_printf("\n");
	}
	ft_printf("\n\n");
}

int main(int argc, char **argv)
{
	t_stacks	stacks;

	if (parse(argc, argv))
	{
		ft_dprintf(2, "Parse Error\n");
		return (1);
	}
	stacks.a = stack_from_argv(argc, argv);
	stacks.b = (void *) 0;
	if (!stacks.a)
		return (1);
	if (solve(&stacks))
	{
		ft_lstclear(&stacks.a, free);
		return (1);
	}
	put_stacks(&stacks);
	ft_lstclear(&stacks.a, free);
	return (0);
}

int	parse(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 1)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!ft_isdigit(argv[i][0]) && argv[i][0] != '-')
			return (1);
		j = 1;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
