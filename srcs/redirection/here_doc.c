#include "minishell.h"

void	here_doc(char *str, t_main *main)
{
	// printf("'%s'\n", str);
	dup2(main->pipefd_here_doc[1], STDOUT_FILENO);
	ft_putstr_fd(str, 1);
	free(str);
	dup2(main->save_fd[1], STDOUT_FILENO);
	dup2(main->pipefd_here_doc[0], STDIN_FILENO); // verif
}

static char	*strjoin_here_doc(char *buff, char *add)
{
	char	*rs;
	size_t	i;
	size_t	j;
	int		size;

	if (buff)
		size = ft_strlen(buff) + ft_strlen(add) + 2;
	else
		size = ft_strlen(add) + 2;
	rs = ft_calloc(size, sizeof(1));
	if (!rs)
		return (0);
	i = 0;
	if (buff)
	{
		while (buff[i])
		{
			rs[i] = buff[i];
			i++;
		}
		free(buff);
	}
	if (add)
	{
		j = 0;
		while (add[j])
		{
			rs[i] = add[j];
			j++;
			i++;
		}
		free(add);
	}
	rs[i] = '\n';
	rs[++i] = '\0';
	return (rs);
}

static void	save(t_redir *redir, t_main *main)
{
	char	*str;
	char	*buff;

	str = 0;
	while (!str || ft_strncmp(str, redir->file, -1))
	{
		buff = redir->buff;
		if (str)
			redir->buff = strjoin_here_doc(buff, str);
		str = readline("> ");
		// buff = strjoin_here_doc();
	}
	free(str);
}

static char	*is_here_doc_redir(t_param_cmd *param, t_main *main)
{
	t_redir	*redir;
	t_list	*redir_lst;
	char	*rs;

	rs = NULL;
	redir_lst = param->redir;
	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type == HERE_DOC)
		{
			save(redir, main);
			rs = redir->buff;
		}
		redir_lst = redir_lst->next;
	}
	return (rs);
}

void	save_here_doc(t_list *param_lst, t_main *main)
{
	t_param_cmd	*param;

	while (param_lst)
	{
		param = (t_param_cmd *)param_lst->content;
		param->here_doc_str = is_here_doc_redir(param, main);
		param_lst = param_lst->next;
	}
}