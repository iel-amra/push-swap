/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:04:29 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 16:33:19 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	is_in_tab(int *tab, int nb, int len)
{
	while (len-- > 0)
	{
		if (*tab++ == nb)
			return (1);
	}
	return (0);
}

int	*tab_int_copy(int *line, int len)
{
	int	*cpy;

	cpy = malloc(len * sizeof(int));
	if (!cpy)
		return ((void *) 0);
	while (--len >= 0)
		cpy[len] = line[len];
	return (cpy);
}

int	*int_copy(int *nb)
{
	int	*cpy;

	cpy = malloc(sizeof(int));
	if (!cpy)
		return ((void *) 0);
	*cpy = *nb;
	return (cpy);
}

//Ne fonctionne que si nb et str ont le meme nombre de chiffres

int	nb_digit(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	overflow(char *str, unsigned int nb, int len)
{
	int				res;

	if (nb / 10)
	{
		res = overflow(str, nb / 10, len - 1);
		if (res != 0)
			return (res);
	}
	if (str[len] < (char)(nb % 10 + '0'))
		return (-1);
	if (str[len] > (char)(nb % 10 + '0'))
		return (1);
	return (0);
}
