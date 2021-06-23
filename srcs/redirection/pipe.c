#include "minishell.h"

void	redir_pipe_before(t_param_cmd *param, t_main *main)
{
	if (dup2(main->pipefd[1 - main->count % 2][0], STDIN_FILENO) == -1)
		quit_prog("dup2() error", main);
	close(main->pipefd[1 - main->count % 2][0]);
	close(main->pipefd[1 - main->count % 2][1]);
}

void	redir_pipe_after(t_param_cmd *param, t_main *main)
{
	if (dup2(main->pipefd[main->count % 2][1], STDOUT_FILENO) == -1)
		quit_prog("dup2() error", main);
	close(main->pipefd[main->count % 2][0]);
	close(main->pipefd[main->count % 2][1]);
}
