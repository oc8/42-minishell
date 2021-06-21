#include "minishell.h"

void	redir_pipe(t_param_cmd *param, t_main *main)
{
	if (param->pipe_after)
	{
		if (dup2(main->pipefd[main->count % 2][1], STDOUT_FILENO) == -1)
			quit_prog("dup2() error", main);
		close(main->pipefd[main->count % 2][0]);
		close(main->pipefd[main->count % 2][1]);
	}
	if (param->pipe_before)
	{
		if (dup2(main->pipefd[1 - main->count % 2][0], STDIN_FILENO) == -1)
			quit_prog("dup2() error", main);
		close(main->pipefd[1 - main->count % 2][0]);
		close(main->pipefd[1 - main->count % 2][1]);
	}
}
