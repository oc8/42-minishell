#include "minishell.h"

static void	cmd_fork(t_param_cmd *param, t_function *fct, t_main *main)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		quit_prog("error fork", main);
	else if (pid == 0)
	{
		redirection(param, main);
		if (!ft_strncmp(param->cmd[0], fct->name, 7))
			fct->fct(param, main);
		else
			cmd_others(param, main);
		if (param->redir)
			close(main->file);
		// if (param->pipe_after || param->pipe_before)
		// {
		// 	close(main->pipefd[0][0]);
		// 	close(main->pipefd[0][1]);
		// }
		exit(0);
	}
	// else
	// 	wait(NULL);
}

void	cmd_call(t_param_cmd *param, t_main *main)
{
	int		i;

	if (!param->cmd[0])
		return ;
	// printf("--> %s\n", param->cmd[0]);
	i = 7;
	while (--i >= 0 && ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
		;
	if ((i != I_CD && i != I_EXPORT && i != I_UNSET && i != I_EXIT) ||		\
			param->pipe_before || param->pipe_after)
		cmd_fork(param, &main->cmd_fct[i], main);
	else
	{
		redirection(param, main);
		main->cmd_fct[i].fct(param, main);
		if (param->redir)
			close(main->file);
		// if (param->pipe_after || param->pipe_before)
		// {
		// 	close(main->pipefd[0][0]);
		// 	close(main->pipefd[0][1]);
		// }
	}
}
