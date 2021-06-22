#include "minishell.h"

void	redir_in(int fd[2], t_main *main)
{
	if (dup2(fd[0], fd[1]) == -1)
		quit_prog("dup2() error", main);
	close(fd[0]);
}
