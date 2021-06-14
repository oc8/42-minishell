#include "minishell.h"

static void	redir_type(int *file2, t_redir *redir, t_main *main)
{
	int		file;

	if (redir->type == REDIR_OUT)
	{
		file = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
		if (file == -1)
			quit_prog("open() error", main);
		*file2 = dup2(file, redir->fd);
	}
	else if (redir->type == APP_REDIR_OUT)
	{
		file = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
		if (file == -1)
			quit_prog("open() error", main);
		*file2 = dup2(file, redir->fd);
	}
	else if (redir->type == REDIR_IN)
	{
		file = open(redir->file, O_CREAT | O_WRONLY, S_IRWXU);
		if (file == -1)
			quit_prog("open() error", main);
		*file2 = dup2(redir->fd, file);
	}
	if (*file2 == -1)
		quit_prog("dup2() error", main);
}

static int	redir_chevron(t_list *redir_lst, t_main *main)
{
	int		flag;
	t_redir	*redir;

	flag = 0;
	while (redir_lst)
	{
		if (flag)
			close(main->file);
		else
			flag = 1;
		redir = (t_redir *)redir_lst->content;
		if (redir->var_err)
			return (cmd_error(0, "ambiguous redirect", redir->var_err, 1));
		redir_type(&main->file, redir, main);
		redir_lst = redir_lst->next;
	}
	return (0);
}

void	redirection(t_param_cmd *param, t_main *main)
{
	if (param->redir)
		redir_chevron(param->redir, main);
	if (param->pipe_after)
	{
		if (dup2(main->pipefd[main->count % 2][1], STDOUT_FILENO) == -1)
			quit_prog("dup2() error", main);
		close(main->pipefd[main->count % 2][0]);
		close(main->pipefd[main->count % 2][1]);
		// ft_putstr_fd("dup2 in", 1);
	}
	if (param->pipe_before)
	{
		if (dup2(main->pipefd[1-main->count % 2][0], STDIN_FILENO) == -1)
			quit_prog("dup2() error", main);
		// ft_putstr_fd("dup2 out", 2);
		close(main->pipefd[1-main->count % 2][0]);
		close(main->pipefd[1-main->count % 2][1]);
	}
}
