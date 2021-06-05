#include "minishell.h"

void	cmd_pwd(t_param_cmd *param, t_main *main)
{
	char	cwd[PWD_MAX_SIZE];
	int		file2;


	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (param->redir)
			close(file2);
		quit_prog("getcwd() on pwd", main);
	}
	else
		printf("%s\n", cwd);
}
