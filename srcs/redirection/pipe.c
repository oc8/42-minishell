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

void	set_pipe(t_param_cmd *param, t_list *param_lst, t_main *main)
{
	param->pipe_before = 0;
	param->pipe_after = 1;
	if (!param_lst->next)
		param->pipe_after = 0;
	if (main->count > 0)
		param->pipe_before = 1;
	if (param->pipe_after)
	{
		if (pipe(main->pipefd[main->count % 2]) == -1)
			quit_prog("pipe()", main);
	}
}

void	close_pipe(t_main *main)
{
	if (main->count > 1)
	{
		close(main->pipefd[main->count % 2][0]);
		close(main->pipefd[main->count % 2][1]);
	}
}
