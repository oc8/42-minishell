#include "minishell.h"

static void	here_doc_or_in(int flag_here_doc, t_param_cmd *param)
{
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

static int	check_redir(t_redir *redir)
{
	if (redir->var_err)
		return (cmd_error(0, "ambiguous redirect", redir->var_err, 1));
	if (redir->fd > 255)
		return (cmd_error(0, "Bad file descriptor", ft_itoa(redir->fd), 1));
	if (redir->fd < 0)
		return (cmd_error(0, \
			"file descriptor out of range: Bad file descriptor", 0, 1));
	return (0);
}

int	open_fd(t_param_cmd *param, t_main *main)
{
	t_list	*redir_lst;
	t_redir	*redir;
	int		flag_here_doc;

	flag_here_doc = 0;
	redir_lst = param->redir;
	while (redir_lst)
	{
		redir = (t_redir *)redir_lst->content;
		if (check_redir(redir))
			return (1);
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
	here_doc_or_in(flag_here_doc, param);
	return (0);
}
