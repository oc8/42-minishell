#include "libft.h"

size_t	ft_doublelen(const void **s)
{
	size_t	i;

	i = 0;
	while (((char **)s)[i])
		i++;
	return (i);
}
