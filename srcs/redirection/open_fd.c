#include "minishell.h"

void	open_fd(t_param_cmd *param, t_main *main)
{
	t_list	*redir_lst;
	t_redir	*redir;
	int		flag_here_doc;

	flag_here_doc = 0;
	redir_lst = param->redir;
	while (redir_lst)
	{
		redir = (t_redir *)redir_lst->content;
		if (redir->var_err)
			cmd_error(0, "ambiguous redirect", redir->var_err, 1);
		if (redir->type == REDIR_OUT || redir->type == APP_REDIR_OUT)
		{
			if (param->file_fd_out[0])
				close(param->file_fd_out[0]);
			if (redir->type == REDIR_OUT)
				param->file_fd_out[0] = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else
				param->file_fd_out[0] = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			param->file_fd_out[1] = redir->fd;
		}
		else if (redir->type == REDIR_IN)
		{
			flag_here_doc = -1;
			if (param->file_fd_in[0])
				close(param->file_fd_in[0]);
			param->file_fd_in[0] = open(redir->file, O_WRONLY, 0644);
			param->file_fd_in[1] = redir->fd;
		}
		else if (redir->type == HERE_DOC)
			flag_here_doc = 1;
		redir_lst = redir_lst->next;
	}
	if (flag_here_doc == 1 && param->file_fd_in[0])
	{
		close(param->file_fd_in[0]);
		param->file_fd_in[0] = 0; // no 0 !
	}
	else if (flag_here_doc == -1 && param->here_doc_str)
	{
		free(param->here_doc_str);
		param->here_doc_str = 0;
	}
}
