#include "minishell.h"

void	redir_in(t_redir *redir, t_main *main)
{
	int		file;

	file = open(redir->file, O_WRONLY, 0644);
	if (file == -1)
	{
		cmd_error(0, strerror(errno), redir->file, 1);
		loop(main); // ?
	}
	if (dup2(file, redir->fd) == -1)
		quit_prog("dup2() error", main);
	close(file);
}
