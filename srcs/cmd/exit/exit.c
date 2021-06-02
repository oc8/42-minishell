#include "minishell.h"

void	cmd_exit(t_param_cmd *param, t_main *main)
{
	int	file2;

	if (param->redir)
		file2 = redirection(param->redir, main);
	if (param->redir)
		close(file2);
	printf("exit\n");
	quit_prog(0, main);
}
