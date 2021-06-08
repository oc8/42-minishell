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
}

static void	redir_chevron(t_list *redir_lst, int *file2, t_main *main)
{
	int	flag;

	flag = 0;
	while (redir_lst)
	{
		if (flag)
			close(*file2);
		else
			flag = 1;
		redir_type(file2, redir_lst->content, main);
		redir_lst = redir_lst->next;
	}
}

static void	redir_pipe(int *file2, t_main *main)
{
	*file2 = dup2(main->pipefd[1], STDOUT_FILENO);
	// printf("tcoest\n");
	// close(main->pipefd[0]);
}

int	redirection(t_param_cmd *param, t_main *main)
{
	int			file2;
	static int	flag = 0;

	if (param->redir)
		redir_chevron(param->redir, &file2, main);
	// if (param->pipe && !flag)
	// {
	// 	redir_pipe(&file2, main);
	// 	flag = 1;
	// }
	// else if (flag)
	// {
	// 	// printf("tcoest\n");
	// 	close(main->pipefd[1]);
	// 	file2 = dup2(STDIN_FILENO, main->pipefd[0]);
	// 	// file2 = dup2(main->pipefd[0], STDIN_FILENO);
	// 	flag = 0;
	// }
	return (file2);
}
