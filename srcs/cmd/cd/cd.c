#include "minishell.h"

void	cmd_cd(t_param_cmd *param, t_main *main)
{
	char	**arg;

	arg = param->cmd + 1;
	if (arg[0][0] == '-' && !arg[0][1])
		;
	else if (arg[0][0] == '~' && !arg[0][1])
	{
		if (chdir(arg[0]) == -1)
			cmd_error("cd", strerror(errno), main->home_path, 1);
		return ;
	}
	if (!ft_strncmp(arg[0], ".", 2))
		return ;
	if (chdir(arg[0]) == -1)
		cmd_error("cd", strerror(errno), arg[0], 1); // strerror ?
}
