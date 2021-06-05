#include "minishell.h"

static void	redir_type(int *file2, t_redir *redir, t_main *main)
{
	int		file;

	if (redir->type == REDIR_OUTPUT)
	{
		file = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
		if (file == -1)
			quit_prog("open() error", main);
		*file2 = dup2(file, redir->fd);
	}
	else if (redir->type == APPEND_REDIR_OUTPUT)
	{
		file = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
		if (file == -1)
			quit_prog("open() error", main);
		*file2 = dup2(file, redir->fd);
	}
	else if (redir->type == REDIR_INPUT)
	{
		file = open(redir->file, O_CREAT | O_WRONLY, S_IRWXU);
		if (file == -1)
			quit_prog("open() error", main);
		*file2 = dup2(redir->fd, file);
	}
}

int	redirection(t_list *redir_lst, t_main *main)
{
	int		file2;
	int		flag;

	flag = 0;
	while (redir_lst)
	{
		if (flag)
			close(file2);
		redir_type(&file2, redir_lst->content, main);
		flag = 1;
		redir_lst = redir_lst->next;
	}
	return (file2);
}
