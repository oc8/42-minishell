#include "libft.h"

char	*ft_strdup_no_list(const char *s1)
{
	char	*s1copy;
	int		i;

	if (!s1)
		return (NULL);
	s1copy = malloc(ft_strlen(s1) + 1);
	if (!s1copy)
		return (0);
	i = -1;
	while (s1[++i])
		s1copy[i] = s1[i];
	s1copy[i] = '\0';
	return (s1copy);
}
