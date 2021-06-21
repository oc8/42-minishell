#include "minishell.h"

static void	cmd_fork(t_param_cmd *param, t_function *fct, t_main *main)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		quit_prog("error fork", main);
	else if (pid == 0)
	{
		if (param->here_doc) // not here
		{
			pipe(main->pipefd_here_doc); // verif // after ?
			here_doc(param->here_doc, main);
		}
		redir_pipe(param, main);
		// redirection(param, main);
		if (!ft_strncmp(param->cmd[0], fct->name, 7))
			fct->fct(param, main);
		else
			cmd_others(param, main);
		// if (param->redir)
		// 	close(main->file);
		close(main->pipefd_here_doc[1]);
		close(main->pipefd_here_doc[0]);
		quit_prog(0, main);
	}
}

void	cmd_call(t_param_cmd *param, t_main *main)
{
	int		i;

	// printf("0\n");
	redirection(param, main);
	// printf("1\n");
	
	// int file;
	// int file2;
	// file = open("o", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// if (file == -1)
	// 	quit_prog("open() error", main);
	// file2 = dup2(file, 1);
	// // close(file2);
	// dup2(main->save_fd[1], 1);
	// return ;
	// close(file);
	if (!param->cmd || !param->cmd[0])
	{
	// printf("2\n");
		if (param->redir)
		{
			dup2(main->save_fd[1], 1);
			// close(3);
	// printf("3\n");
		}
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
		// redirection(param, main);
		main->cmd_fct[i].fct(param, main);
			// if (param->redir)
	// 	close(main->file);
	}
	if (param->redir)
		dup2(main->save_fd[1], 1);
	// dup2(main->save_fd[0], 0);
}
