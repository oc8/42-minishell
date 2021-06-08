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
	int		pipefd1[2];
	int		pipefd2[2];
	int		*file2;
	int		count;

	count = 0;
	while (param_lst)
	{
		if (count == 0 && param_lst->next)
		{
			if (pipe(main->pipefd) == -1)
				quit_prog("pipe()", main);
			// *file2 = dup2(main->pipefd[1], STDOUT_FILENO);
		}
		cmd_call(param_lst->content, main);
		count++;
		param_lst = param_lst->next;
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	// close(main->pipefd[0]);
	// close(main->pipefd[1]);
}

static void	cmd_fork(t_param_cmd *param, t_function *fct, t_main *main)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		quit_prog("error fork", main);
	else if (pid == 0)
	{
		if (param->redir || param->pipe)
			main->file = redirection(param, main);
		if (!ft_strncmp(param->cmd[0], fct->name, 7))
		{
			main->file = dup2(main->pipefd[1], STDOUT_FILENO);
			fct->fct(param, main);
		}
		else
		{
			main->file = dup2(main->pipefd[0], STDIN_FILENO);
			// printf("ok?\n");
			// cmd_others(param, main);
			// close(main->file);
			// close(main->pipefd[0]);
			// close(main->pipefd[1]);
			// printf("close\n");
		}
		if (param->redir || param->pipe)
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
	if (param->pipe || (i != I_CD && i != I_EXPORT && i != I_UNSET && i != I_EXIT))
		cmd_fork(param, &main->cmd_fct[i], main);
	else
	{
		if (param->redir || param->pipe)
			main->file = redirection(param, main);
		main->cmd_fct[i].fct(param, main);
		if (param->redir || param->pipe)
			close(main->file);
	}
	save_last_arg(param->cmd, main);
}
