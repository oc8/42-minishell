#include "minishell.h"

static void	save_last_arg(char **cmd, t_main *main)
{
	size_t	i;
	int		index;
	char	*tmp;

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

void	cmd_exec(t_list *param_lst, t_main *main)
{
	int			*file2;
	int			count;
	t_param_cmd	*param;

	param->pipe_before = 0;
	param->pipe_after = 1;
	count = 0;
	while (param_lst)
	{
		param = (t_param_cmd *)param_lst->content;
		if (!param_lst->next)
			param->pipe_after = 0;
		if (count > 0)
			param->pipe_before = 1;
		if (count % 2 == 0 && param_lst->next)
		{
			printf("pipe[0] creat\n");
			if (pipe(main->pipefd[0]) == -1)
				quit_prog("pipe()", main);
		}
		// if (count % 2 == 0 && param_lst->next)
		// {
		// 	close(main->pipefd[0][0]);
		// 	close(main->pipefd[0][1]);
		// }
		cmd_call(param, main);
		save_last_arg(param->cmd, main);
		count++;
		param_lst = param_lst->next;
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		;
}

static void	cmd_fork(t_param_cmd *param, t_function *fct, t_main *main)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		quit_prog("error fork", main);
	else if (pid == 0)
	{
		redirection(param, main);
		if (!ft_strncmp(param->cmd[0], fct->name, 7))
			fct->fct(param, main);
		else
			cmd_others(param, main);
		if (param->redir)
			close(main->file);
		exit(0);
	}
}

void	cmd_call(t_param_cmd *param, t_main *main)
{
	int		i;

	if (!param->cmd[0])
		return ;
	i = 7;
	while (--i >= 0 && ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
		;
	if ((i != I_CD && i != I_EXPORT && i != I_UNSET && i != I_EXIT) ||		\
			param->pipe_before || param->pipe_after)
		cmd_fork(param, &main->cmd_fct[i], main);
	else
	{
		redirection(param, main);
		main->cmd_fct[i].fct(param, main);
		if (param->redir)
			close(main->file);
	}
}
