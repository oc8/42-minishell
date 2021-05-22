#include "libft.h"

static t_list	**ml_pointer(void)
{
	static t_list	*wrm;

	return (&wrm);
}

void	*ml(size_t size)
{
	char	*buffer;
	t_list	*new_elem;

	buffer = NULL;
	buffer = malloc(size);
	if (!buffer)
	{
		ml_destroy();
		return (0);
	}
	new_elem = NULL;
	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
	{
		free(buffer);
		ml_destroy();
		return (0);
	}
	new_elem->content = buffer;
	new_elem->next = 0;
	ft_lstadd_back(ml_pointer(), new_elem);
	return (buffer);
}

int	ml_free(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	prev = 0;
	wrstart = ml_pointer();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*wrstart = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	ml_destroy(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	wrstart = ml_pointer();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*wrstart = 0;
}
