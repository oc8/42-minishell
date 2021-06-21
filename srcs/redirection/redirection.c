#include "minishell.h"

static int	redir_chevron(t_list *redir_lst, t_main *main)
{
	t_redir	*redir;

	while (redir_lst)
	{
		redir = (t_redir *)redir_lst->content;
		if (redir->var_err)
			return (cmd_error(0, "ambiguous redirect", redir->var_err, 1));
		if (redir->type == REDIR_OUT || redir->type == APP_REDIR_OUT)
			redir_out(redir, main);
		else if (redir->type == REDIR_IN)
			redir_in(redir, main);
		// else if (redir->type == HERE_DOC)
		// 	here_doc(redir, main);
		redir_lst = redir_lst->next;
	}
	return (0);
}

void	redirection(t_param_cmd *param, t_main *main)
{
	if (param->redir)
		redir_chevron(param->redir, main);
}
