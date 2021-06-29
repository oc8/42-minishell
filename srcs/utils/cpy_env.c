#include "minishell.h"

char	**cpy_env(char *env[], t_main *main)
{
	char	**rs;
	size_t	i;
	size_t	len;

	len = ft_doublelen((const void **)env) + 1;
	main->nbr_env = len - 1;
	main->max = len * 2;
	rs = ft_calloc_lst(&main->free, main->max + 1, sizeof(char *));
	if (!rs)
		quit_prog("malloc() error", main);
	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]) + 1;
		rs[i] = ft_calloc_lst(&main->free, len, sizeof(char));
		ft_strlcpy(rs[i], env[i], len);
		// printf("%s | %s : %zu\n", env[i], rs[i], len);
		i++;
	}
	rs[i] = 0;
	return (rs);
}