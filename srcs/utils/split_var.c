#include "minishell.h"

char	**split_var(char *var, t_main *main)
{
	char	**rs;
	size_t	i;
	size_t	equal;

	rs = ft_calloc(3, sizeof(char *));
	if (!rs)
		quit_prog("malloc error", main);
	equal = 0;
	while (var[equal] && var[equal] != '=')
		equal++;
	if (var[equal] != '=')
	{
		free(rs);
		return (0);
	}
	rs[0] = ft_calloc(equal, sizeof(char));
	if (!rs)
		quit_prog("malloc error", main);
	i = 0;
	while (i < equal)
	{
		rs[0][i] = var[i];
		i++;
	}
	rs[0][i] = 0;
	rs[1] = ft_calloc(ft_strlen(&var[i + 1]), sizeof(char));
	if (!rs)
		quit_prog("malloc error", main);
	i = 0;
	while (var[++equal])
		rs[1][i++] = var[equal];
	rs[2] = 0;
	return (rs);
}
