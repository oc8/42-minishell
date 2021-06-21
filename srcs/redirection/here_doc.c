#include "minishell.h"

// static char	*strjoin_here_doc(char *buff)
// {

// }

void	save_here_doc(t_redir *redir, t_main *main)
{
	char	*str;
	char	*buff;

	str = 0;
	redir->buff = ft_strdup_no_list("");
	while (!str || ft_strncmp(str, redir->file, -1))
	{
		buff = redir->buff;
		if (str)
		{
			redir->buff = ft_strjoin(buff, str);
			free(str);
			free(buff);
		}
		str = readline("> ");
		// buff = strjoin_here_doc();
	}
	if (str)
		free(str);
}

void	here_doc(t_redir *redir, t_main *main)
{

	printf("'%s'\n", redir->buff);
	dup2(main->pipefd_here_doc[1], STDOUT_FILENO);
	ft_putstr_fd(redir->buff, 1);
	free(redir->buff);
	dup2(main->save_fd[1], STDOUT_FILENO);
	dup2(main->pipefd_here_doc[0], STDIN_FILENO); // verif
}
