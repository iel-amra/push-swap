/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:34:49 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/17 17:44:19 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!new)
		return (1);
	new->next = *alst;
	*alst = new;
	return (0);
}
