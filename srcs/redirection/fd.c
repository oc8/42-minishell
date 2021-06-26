#include "minishell.h"

// void	check_fd(t_param_cmd *param, t_main *main)
// {
// 	t_list	*redir_lst;
// 	t_redir	*redir;
// 	int		fd;

// 	redir_lst = param->redir;
// 	while (redir_lst)
// 	{
// 		redir = (t_redir *)redir_lst->content;
// 		if (redir->type == REDIR_IN)
// 		{	
// 			fd = open(redir->file, O_RDONLY, 0644);
// 			if (fd == -1)
// 			{
// 				cmd_error(0, strerror(errno), redir->file, 1);
// 				loop(main);
// 			}
// 			close(fd);
// 		}
// 		redir_lst = redir_lst->next;
// 	}
// }

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
			main->exit_status = cmd_error(0, "ambiguous redirect", redir->var_err, 1);
		if (redir->type == REDIR_OUT || redir->type == APP_REDIR_OUT)
			open_fd_out(param->file_fd_out, redir, main);
		else if (redir->type == REDIR_IN)
		{
			flag_here_doc = -1;
			open_fd_in(param->file_fd_in, redir, main);
		}
		else if (redir->type == HERE_DOC)
			flag_here_doc = 1;
		redir_lst = redir_lst->next;
	}
	if (flag_here_doc == 1 && param->file_fd_in[0])
	{
		close(param->file_fd_in[0]);
		param->file_fd_in[0] = 0;
	}
	else if (flag_here_doc == -1 && param->here_doc_str)
	{
		free(param->here_doc_str);
		param->here_doc_str = 0;
	}
}
