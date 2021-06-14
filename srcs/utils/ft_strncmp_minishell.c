#include "libft.h"

int	ft_strncmp_minishell(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL)
		return (1);
	if (n < 1)
		return (0);
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}
