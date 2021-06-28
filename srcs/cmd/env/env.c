#include "minishell.h"

void	cmd_env(t_param_cmd *param, t_main *main)
{
	size_t	i;

	(void)param;
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
