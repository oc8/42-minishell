#include "minishell.h"

static void	free_redirection(void *to_free)
{
	t_redir	*redir;

	redir = (t_redir*)to_free;
	free(redir->file);
	free(redir->var_err);
	free(redir);
}

void	free_param_cmd(t_param_cmd *param)
{
	int	i;

	if (param->cmd)	// METTRE DOUBLESTR FREE !!!!!
	{
		i = -1;
		while (param->cmd[++i])
			free(param->cmd[i]);
		free(param->cmd);
		param->cmd = NULL;
	}
	ft_lstclear(&param->redir, free_redirection);
}