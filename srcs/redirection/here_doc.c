#include "minishell.h"

void	here_doc(char *str, t_main *main)
{
	dup2(main->pipefd_here_doc[1], STDOUT_FILENO);
	ft_putstr_fd(str, 1);
	free(str);
	dup2(main->save_fd[1], STDOUT_FILENO);
	dup2(main->pipefd_here_doc[0], STDIN_FILENO);
	close(main->pipefd_here_doc[1]);
	close(main->pipefd_here_doc[0]);
}
