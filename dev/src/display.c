/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:02:55 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:22:29 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
			ft_dprintf(2, "%i     ", int_content(stacks.a));
			stacks.a = stacks.a->next;
		}
		else
			ft_dprintf(2, "      ");
		if (stacks.b)
		{
			ft_dprintf(2, "%i\n", int_content(stacks.b));
			stacks.b = stacks.b->next;
		}
		else
			ft_dprintf(2, "\n");
	}
	ft_dprintf(2, "\n\n");
}

void	print_tab(int *tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		ft_printf("%i ", tab[i]);
		i++;
	}
	ft_printf("\n");
}
