#include "minishell.h"

void	redir_out(t_redir *redir, t_main *main)
{
	int		file;

	if (redir->type == REDIR_OUT)
		file = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		file = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file == -1)
		quit_prog("open() error", main);
	if (dup2(file, redir->fd) == -1)
		quit_prog("dup2() error", main);
	close(file);
}
