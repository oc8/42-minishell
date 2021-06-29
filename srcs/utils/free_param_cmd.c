#include "minishell.h"

static void	free_redirection(void *to_free)
{
	t_redir	*redir;

	redir = (t_redir *)to_free;
	free(redir->file);
	free(redir->var_err);
	free(redir);
}

void	free_param_cmd(void *ptr)
{
	t_param_cmd	*param;
	int			i;

	param = (t_param_cmd *)ptr;
	if (param->cmd)
		ft_freedoublestr(&param->cmd);
	free(param->here_doc_str);
	param->here_doc_str = NULL;
	ft_lstclear(&param->redir, free_redirection);
}
