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
	while (param_lst)
	{
		cmd_call(param_lst->content, main);
		param_lst = param_lst->next;
	}
}

void	cmd_call(t_param_cmd *param, t_main *main)
{
	int		i;
	pid_t	pid;
	int		status;
	// int		pipefd[2];

	if (!param->cmd[0])
		return ;
	i = 7;
	while (--i >= 0 && ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
		;
	if (param->pipe || (i != I_CD && i != I_EXPORT && i != I_UNSET && i != I_EXIT))
	{
		// if (pipe(pipefd) == -1)
		// 	quit_prog("pipe()", main);
		// *file2 = dup2(STDIN_FILENO, STDOUT_FILENO);
		pid = fork();
		if (pid == -1)
			quit_prog("error fork", main);
		else if (pid == 0)
		{
			if (!ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
			{
				if (param->redir || param->pipe)
					main->file = redirection(param, main);
				main->cmd_fct[i].fct(param, main);
				if (param->redir || param->pipe)
					close(main->file);
			}
			else
				cmd_others(param, main);
			exit(0);
		}
		else
			wait(&status);
	}
	else
	{
		if (param->redir)
			main->file = redirection(param, main);
		main->cmd_fct[i].fct(param, main);
		if (param->redir)
			close(main->file);
	}
	// close(main->pipefd[0]);
	// close(main->pipefd[1]);
	save_last_arg(param->cmd, main);
}
