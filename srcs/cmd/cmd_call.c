#include "minishell.h"

static void	cmd_fork(t_param_cmd *param, t_function *fct, t_main *main)
{
	if (param->here_doc_str)
	{
		if (pipe(main->pipefd_here_doc) == -1)
			quit_prog("pipe()", main);
	}
	main->pid[main->pid_nbr] = fork();
	if (main->pid[main->pid_nbr] == -1)
		quit_prog("error fork", main);
	else if (main->pid[main->pid_nbr] == 0)
	{
		redir(param, main);
		if (!ft_strncmp(param->cmd[0], fct->name, 7))
			fct->build_in(param, main);
		else
			cmd_build_out(param, main);
		free_all(main);
		exit(g_global.exit_status);
	}
	if (param->here_doc_str)
	{
		close(main->pipefd_here_doc[1]);
		close(main->pipefd_here_doc[0]);
	}
	main->pid_nbr += 1;
}

void	cmd_call(t_param_cmd *param, t_main *main)
{
	int		i;

	if (open_fd(param, main) || !param->cmd || !param->cmd[0])
	{
		if (param->redir)
			dup2(main->save_fd[1], 1);
		return ;
	}
	i = 7;
	while (--i >= 0 && ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
		;
	if ((i != I_CD && i != I_EXPORT && i != I_UNSET && i != I_EXIT) || \
			param->pipe_before || param->pipe_after)
		cmd_fork(param, &main->cmd_fct[i], main);
	else
	{
		if (param->file_fd_out[0])
			redir_out(param->file_fd_out, main);
		main->cmd_fct[i].build_in(param, main);
	}
	close_redir(param, main);
}
