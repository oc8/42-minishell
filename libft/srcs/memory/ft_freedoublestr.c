#include "libft.h"

void	ft_freedoublestr(char **src)
{
	size_t	i;

	i = 0;
	while (src[i])
		free(src[i++]);
	free(src);
}
