#include "libft.h"

static int	is_first(t_list *elem, t_list **lst, void *content)
{
	if (elem->content == content)
	{
		*lst = (*lst)->next;
		free(elem);
		return (1);
	}
	return (0);
}

void	ft_lstdel_content(t_list **lst, void *content)
{
	t_list	*tmp;
	t_list	*elem;

	elem = *lst;
	if (content == NULL)
		return ;
	if (is_first(elem, lst, content))
		return ;
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
