#include "libft.h"

void	ft_lstdel_content(t_list **lst, void *content)
{
	t_list	*tmp;
	t_list	*elem;

	elem = *lst;
	if (content == NULL)
		return ;
	if (elem->content == content)
	{
		*lst = (*lst)->next;
		free(elem);
		return ;
	}
	while (elem)
	{
		if (elem->content == content)
		{
			tmp->next = elem->next;
			free(elem);
			elem = tmp->next;
		}
		else
		{
			tmp = elem;
			elem = elem->next;
		}
	}
}
