/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:02:50 by iel-amra          #+#    #+#             */
/*   Updated: 2022/07/17 17:28:10 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;
	
	if (!content)
		return ((void *) 0);
	elem = malloc(sizeof(t_list));
	if (!elem)
		return ((void *) 0);
	elem->content = content;
	elem->next = ((void *) 0);
	return (elem);
}
