#include "libft.h"

void	ft_freedoublestr(char ***src)
{
	size_t	i;

	if (*src == NULL)
		return ;
	i = 0;
	while ((*src)[i])
	{
		free((*src)[i]);
		i++;
	}
	free((*src));
	(*src) = NULL;
}
