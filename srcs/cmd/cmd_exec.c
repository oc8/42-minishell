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
	t_param_cmd	*param;

	main->count = 0;
	main->i_pipe = 0;
	while (param_lst)
	{
		param = (t_param_cmd *)param_lst->content;
		param->pipe_before = 0;
		param->pipe_after = 1;
		if (!param_lst->next)
			param->pipe_after = 0;
		if (main->count > 0)
			param->pipe_before = 1;

		if (main->count % 2 == 0 && param->pipe_after)
		{
			// printf("pipe[0] creat\n");
			if (pipe(main->pipefd[0]) == -1)
				quit_prog("pipe()", main);
			// main->i_pipe = 0;
		}
		else if (main->count % 2 == 1 && param->pipe_after)
		{
			if (pipe(main->pipefd[1]) == -1)
				quit_prog("pipe()", main);
			// main->i_pipe = 1;
		}
		// if (main->count == 2)
		// 	main->i_pipe = 1;
		cmd_call(param, main);
		save_last_arg(param->cmd, main);
		main->count++;
		if (main->count % 2 == 0)
		{
			close(main->pipefd[0][0]);
			close(main->pipefd[0][1]);
		}
		else if (main->count > 1 && main->count % 2 == 1)
		{
			close(main->pipefd[1][0]);
			close(main->pipefd[1][1]);
		}
		param_lst = param_lst->next;
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		;
}
