#include "minishell.h"

void	cmd_pwd(char **arg, t_main *main)
{
	char	cwd[PWD_MAX_SIZE];

	(void)main;
	(void)arg;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		quit_prog("getcwd() on pwd", main);
	else
		printf("%s\n", cwd);
}
