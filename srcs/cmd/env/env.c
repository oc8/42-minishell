#include "minishell.h"

// static int	contain_char(char *var, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (var[i] && var[i] != c)
// 		i++;
// 	if (var[i] == c)
// 		return (1);
// 	return (0);
// }

void	cmd_env(t_param_cmd *param, t_main *main)
{
	size_t	i;

	i = 0;
	while (main->env[i] && i < main->nbr_env)
	{
		if (ft_strchr(main->env[i], '=') && ft_strncmp(main->env[i], "_=", 2))
			printf("%s\n", main->env[i]);
		else if (!ft_strncmp(main->env[i], "_=", 2))
			printf("_=/usr/bin/env\n");
		i++;
	}
}
