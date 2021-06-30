#include "minishell.h"

char	*save_path_home(char **env, t_main *main)
{
	int		i;
	char	*path_home;
	int		size;
	char	**var;

	i = var_defined("HOME", main);
	if (i == -1)
		return (0);
	var = split_var(env[i], main);
	size = ft_strlen(var[1]) + 1;
	path_home = ft_calloc_lst(&main->free, size, sizeof(char));
	if (!path_home)
		quit_prog("malloc()", main);
	ft_strlcpy(path_home, var[1], size);
	ft_freedoublestr(&var);
	return (path_home);
}
