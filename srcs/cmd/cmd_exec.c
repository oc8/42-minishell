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

void	cmd_exec(t_list *param_lst, t_main *main)
{
	t_param_cmd	*param;
	int			*count;

	save_here_doc(param_lst, main);
	main->pid_nbr = 0;
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
	// int	i;
	// i = -1;
	// while (main->pid[++i])
	// 	main->exit_status = waitpid(main->pid[i], NULL, WNOHANG);
}
