#include "libft.h"

t_list	*ft_lstget(t_list *lst, int i)
{
	while (i > 0)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
}
