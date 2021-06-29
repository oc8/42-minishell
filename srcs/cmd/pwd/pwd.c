#include "minishell.h"

void	cmd_pwd(t_param_cmd *param, t_main *main)
{
	char	cwd[PWD_MAX_SIZE];

	(void)param;
	(void)main;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (!main->pwd)
			cmd_error("pwd", strerror(errno), 0, 1);
		else
			printf("%s\n", main->pwd);
	}
	else
	{
		printf("%s\n", cwd);
		// free(cwd);
	}
}
