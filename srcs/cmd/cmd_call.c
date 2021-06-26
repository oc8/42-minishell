#include "minishell.h"

static void	cmd_fork(t_param_cmd *param, t_function *fct, t_main *main)
{
	// pid_t	pid;

	if (param->here_doc_str)
	{
		pipe(main->pipefd_here_doc);
	} // verif // after ?
	main->pid[main->pid_nbr] = fork();
	if (main->pid[main->pid_nbr] == -1)
		quit_prog("error fork", main);
	else if (main->pid[main->pid_nbr] == 0)
	{
		if (param->pipe_before)
			redir_pipe_before(param, main);
		if (param->here_doc_str) // not here
		{
			here_doc(param->here_doc_str, main);
			close(main->pipefd_here_doc[1]);
			close(main->pipefd_here_doc[0]);
		}
		if (param->pipe_after)
			redir_pipe_after(param, main);
		if (param->file_fd_in[0])
			redir_in(param->file_fd_in, main);
		if (param->file_fd_out[0])
			redir_out(param->file_fd_out, main);

		if (!ft_strncmp(param->cmd[0], fct->name, 7))
			fct->fct(param, main);
		else
			cmd_others(param, main);
		free_all(main);
		exit(main->exit_status);
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

	open_fd(param, main);
	if (!param->cmd || !param->cmd[0])
	{
		if (param->redir)
			dup2(main->save_fd[1], 1);
		return ;
	}
	i = 7;
	while (--i >= 0 && ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
		;
	if ((i != I_CD && i != I_EXPORT && i != I_UNSET && i != I_EXIT) ||		\
			param->pipe_before || param->pipe_after)
		cmd_fork(param, &main->cmd_fct[i], main);
	else
	{
		if (param->file_fd_out[0])
			redir_out(param->file_fd_out, main);
		main->cmd_fct[i].fct(param, main);
	}
	//
	if (param->file_fd_in[0])
		close(param->file_fd_in[0]);
	if (param->file_fd_out[0])
		close(param->file_fd_out[0]);
	if (param->redir)
		dup2(main->save_fd[1], 1);
	// dup2(main->save_fd[0], 0);
}
