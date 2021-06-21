#include "minishell.h"

static void	save_last_arg(char **cmd, t_main *main)
{
	size_t	i;
	int		index;
	char	*tmp;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
		i++;
	if (!i)
		return ;
	index = var_defined("_", main);
	if (index > -1)
		edit_var(cmd[i - 1], index, main);
	else
	{
		tmp = ft_strjoin("_=", cmd[i - 1]);
		new_var(tmp, main);
		free(tmp);
	}
}

static void	*is_here_doc_redir(t_param_cmd *param, t_main *main)
{
	t_redir	*redir;
	t_list	*redir_lst;

	redir_lst = param->redir;
	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type == HERE_DOC)
		{
			save_here_doc(redir, main);
			return (redir);
		}
		redir_lst = redir_lst->next;
	}
	return (0);
}

void	cmd_exec(t_list *param_lst, t_main *main)
{
	int			*file2;
	t_param_cmd	*param;
	int			*count;
	t_list		*save;

	save = param_lst;
	while (param_lst)
	{
		param = (t_param_cmd *)param_lst->content;
		param->here_doc = is_here_doc_redir(param, main);
		param_lst = param_lst->next;
	}
	param_lst = save;
	main->count = 0;
	while (param_lst)
	{
		param = (t_param_cmd *)param_lst->content;
		param->pipe_before = 0;
		param->pipe_after = 1;
		if (!param_lst->next)
			param->pipe_after = 0;
		if (main->count > 0)
			param->pipe_before = 1;
		if (param->pipe_after)
		{
			// printf("pipe[0] creat\n");
			if (pipe(main->pipefd[main->count % 2]) == -1)
				quit_prog("pipe()", main);
		}
		cmd_call(param, main);
		save_last_arg(param->cmd, main);
		main->count += 1;
		if (main->count > 1)
		{
			close(main->pipefd[main->count % 2][0]);
			close(main->pipefd[main->count % 2][1]);
		}
		param_lst = param_lst->next;
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		;
}
