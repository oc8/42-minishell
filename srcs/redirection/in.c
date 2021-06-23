#include "minishell.h"

void	redir_in(int fd[2], t_main *main)
{
	if (dup2(fd[0], fd[1]) == -1)
		quit_prog("dup2() error", main);
	close(fd[0]);
}

void	open_fd_in(int fd[2], t_redir *redir, t_main *main)
{
	if (fd[0])
		close(fd[0]);
	fd[0] = open(redir->file, O_RDONLY, 0644);
	if (fd[0] == -1)
	{
		cmd_error(0, strerror(errno), redir->file, 1);
		loop(main);
	}
	fd[1] = redir->fd;
}
