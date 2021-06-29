#include "libft.h"

void	**realloc_double(size_t new_size, void ***src)
{
	void	**rs;
	size_t	i;

	rs = ft_calloc(new_size, sizeof(void *));
	i = 0;
	while (*src[i])
	{
		rs[i] = *src[i];
		i++;
	}
	free(*src);
	return (rs);
}
