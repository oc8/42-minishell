#include "libft.h"

void	ft_lstdel_content(t_list *lst, void *content)
{
	t_list	*tmp;

	while (lst)
	{
		if (lst->content == content)
		{
			tmp->next = lst->next;
			free(lst);
			lst = tmp->next;
		}
		else
		{
			tmp = lst;
			lst = lst->next;
		}
	}
}
