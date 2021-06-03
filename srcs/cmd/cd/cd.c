#include "minishell.h"

void	cmd_cd(t_param_cmd *param, t_main *main)
{
	int		file2;
	char	**arg;

	arg = param->cmd + 1;
	if (param->redir)
		file2 = redirection(param->redir, main);
	if (param->redir)
		close(file2);
	if (!ft_strncmp(arg[0], ".", 2))
		return ;
	if (chdir(arg[0]) == -1)
		// quit_prog("chdir() on cd", main);
		cmd_error("cd", strerror(errno), arg[0], 1); // strerror ?
}
