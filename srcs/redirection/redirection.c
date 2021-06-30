#include "minishell.h"

void	redir(t_param_cmd *param, t_main *main)
{
	if (param->pipe_before)
		redir_pipe_before(main);
	if (param->here_doc_str)
		here_doc(param->here_doc_str, main);
	if (param->pipe_after)
		redir_pipe_after(main);
	if (param->file_fd_in[0])
		redir_in(param->file_fd_in, main);
	if (param->file_fd_out[0])
		redir_out(param->file_fd_out, main);
}

void	close_redir(t_param_cmd *param, t_main *main)
{
	if (param->file_fd_in[0])
		close(param->file_fd_in[0]);
	if (param->file_fd_out[0])
		close(param->file_fd_out[0]);
	if (param->redir)
		dup2(main->save_fd[1], 1);
}
