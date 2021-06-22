#include "minishell.h"

// static int	redir_chevron(t_param_cmd *param, t_main *main) // no
// {
// 	t_redir	*redir;
// 	t_list	*redir_lst;

// 	redir_lst = param->redir;
// 	while (redir_lst)
// 	{
// 		redir = (t_redir *)redir_lst->content;
// 		if (redir->var_err)
// 			return (cmd_error(0, "ambiguous redirect", redir->var_err, 1));
// 		if (redir->type == REDIR_OUT || redir->type == APP_REDIR_OUT)
// 		{
// 			redir_out(param->file_fd_out, main);
// 			// param->flag_in_file = 1;
// 		}
// 		else if (redir->type == REDIR_IN)
// 			redir_in(param->file_fd_in, main);
// 		// else if (redir->type == HERE_DOC)
// 		// 	here_doc(redir, main);
// 		redir_lst = redir_lst->next;
// 	}
// 	return (0);
// }

// void	redirection(t_param_cmd *param, t_main *main)
// {
// 	if (param->redir)
// 		redir_chevron(param, main);
// }
