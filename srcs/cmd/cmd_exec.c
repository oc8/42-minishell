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

static void	wait_fork(t_main *main)
{
	size_t	i;
	int		exit_status;

	i = 0;
	while (i < main->pid_nbr)
	{
		waitpid(main->pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			global.exit_status = WEXITSTATUS(exit_status);
		i++;
	}
}

void	cmd_exec(t_list *param_lst, t_main *main)
{
	t_param_cmd	*param;

	save_here_doc(param_lst, main);
	main->pid_nbr = 0;
	main->count = 0;
	while (param_lst)
	{
		param = (t_param_cmd *)param_lst->content;
		set_pipe(param, param_lst, main);
		cmd_call(param, main);
		save_last_arg(param->cmd, main);
		main->count += 1;
		close_pipe(main);
		param_lst = param_lst->next;
	}
	wait_fork(main);
}
