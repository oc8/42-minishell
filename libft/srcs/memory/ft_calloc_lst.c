#include "libft.h"

void	*ft_calloc_lst(t_list **malloc_lst, size_t nbr, size_t size)
{
	void	*rs;
	t_list	*content;

	rs = ft_calloc(nbr, size);
	if (!rs)
		return (0);
	if (!*malloc_lst)
	{
		*malloc_lst = ft_lstnew(rs);
		if (!*malloc_lst)
			return (0);
	}
	else
	{
		content = ft_lstnew(rs);
		if (!content)
			return (0);
		ft_lstadd_front(malloc_lst, content);
	}
	return (rs);
}
