/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:51:16 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 16:33:34 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	reader(t_stacks *stacks)
{
	char	*inst;
	int		i;
	int		len;

	inst = get_next_line(0);
	while (inst)
	{
		len = ft_strlen(inst);
		if (inst[len - 1] == '\n')
			inst[len - 1] = '\0';
		i = 0;
		while (i < 11 && ft_strcmp(str_move[i], inst) != 0)
			i++;
		if (ft_strcmp(str_move[i], inst) == 0)
			move(stacks, i, 0);
		else
		{
			ft_dprintf(2, "Error\n");
			free(inst);
			return (1);
		}
		free(inst);
		inst = get_next_line(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc == 1)
		return (0);
	if (parse(argc, argv))
	{
		ft_dprintf(2, "Error\n");
		return (1);
	}
	stacks.a = stack_from_argv(argc, argv);
	stacks.b = (void *) 0;
	if (!stacks.a)
		return (1);
	if (reader(&stacks))
	{
		ft_lstclear(&stacks.a, free);
		ft_lstclear(&stacks.b, free);
		return (1);
	}
	if (is_sorted(&stacks))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_lstclear(&stacks.a, free);
	return (0);
}
