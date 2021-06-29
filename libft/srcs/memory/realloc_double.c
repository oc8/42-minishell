#include "libft.h"

void	**realloc_double(size_t new_size, void ***src)
{
	void	**rs;
	size_t	i;

	rs = ft_calloc(new_size + 1, sizeof(void *));
	if (*src == NULL)
		return (rs);
	i = 0;
	while ((*src)[i])
	{
		rs[i] = (*src)[i];
		i++;
	}
	free(*src);
	*src = NULL;
	rs[new_size] = NULL;
	return (rs);
}
