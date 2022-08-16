/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:54:06 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 11:56:07 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_factoriel(int nb)
{
	int	res;

	res = 1;
	while (nb > 1)
	{
		res *= nb;
		nb--;
	}
	return (res);
}

int	ft_pow(int nb, int exp)
{
	int	res;

	res = 1;
	while (exp-- > 0)
		res *= nb;
	return (res);
}

int	get_nb_bit(int nb)
{
	int	n_bit;

	if (nb == 0)
		return (1);
	n_bit = 0;
	while (nb > 0)
	{
		n_bit++;
		nb /= 2;
	}
	return (n_bit);
}

int	true_bits(int x)
{
	unsigned long	i;
	int				nb;

	nb = 0;
	i = 0;
	while (i < sizeof(int))
	{
		if (x >> i & 1)
			nb++;
		i++;
	}
	return (nb);
}
