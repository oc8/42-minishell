#include "minishell.h"

void	cmd_env(char **arg, t_main *main)
{
	size_t	i;

	(void)arg;
	i = 0;
	while (main->env[i])
		printf("%s\n", main->env[i++]);
}
