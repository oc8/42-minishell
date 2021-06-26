#include "minishell.h"

void	cmd_pwd(t_param_cmd *param, t_main *main)
{
	char	cwd[PWD_MAX_SIZE];
	int		file2;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cmd_error("pwd", strerror(errno), 0, 1);
	else
		printf("%s\n", cwd);
}
