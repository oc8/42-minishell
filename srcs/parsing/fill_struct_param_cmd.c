#include "minishell.h"

static char	*strjoin_here_doc(char **buff, char **add)
{
	char	*rs;
	size_t	i;
	size_t	j;
	int		size;

	if (*buff)
		size = ft_strlen(*buff) + ft_strlen(*add) + 2;
	else
		size = ft_strlen(*add) + 2;
	rs = ft_calloc(size, sizeof(1));
	if (!rs)
		return (0);
	i = 0;
	if (*buff)
	{
		while ((*buff)[i])
		{
			rs[i] = (*buff)[i];
			i++;
		}
		free(*buff);
		*buff = NULL;
	}
	if (*add)
	{
		j = 0;
		while ((*add)[j])
		{
			rs[i] = (*add)[j];
			j++;
			i++;
		}
		free(*add);
		*add = NULL;
	}
	rs[i] = '\n';
	rs[++i] = '\0';
	return (rs);
}

static void	update_here_doc(char *end, t_param_cmd *param, t_main *main)
{
	char	*new_line;
	char	*with_var;
	char	*here_doc;

	here_doc = NULL;
	with_var = NULL;
	new_line = NULL;
	while (ft_strncmp_minishell(here_doc, end, -1))
	{
		new_line = readline("> ");
		treat_here_doc_line(&with_var, new_line, main);
		printf("with_var = %s\n", with_var);
		here_doc = strjoin_here_doc(&here_doc, &with_var);
		free(new_line);
		new_line = NULL;
		// free(with_var);
		// with_var = NULL;
	}
	param->here_doc_str = here_doc;
	printf("here_doc = %s\n", param->here_doc_str);
}

static void	update_command(t_lexer *lex, t_param_cmd *param, t_main *main)
{
	char	**new;
	int		i;

	i = 0;
	param->n_cmd++;
	new = malloc(sizeof(char *) * (param->n_cmd + 1));
	if (new == NULL)
		quit_prog("Fill_struct : command part malloc", main);
	if (param->cmd)
	{
		while (param->cmd[i])
		{
			new[i] = ft_strdup_no_list(param->cmd[i]);
			if (!new[i++])
				quit_prog("Fill_struct : command part malloc", main);
		}
	}
	new[i] = ft_strdup_no_list(lex->value);
	if (!new[i])
		quit_prog("Fill_struct : command part malloc", main);
	new[++i] = NULL;
	ft_freedoublestr(&param->cmd);
	param->cmd = new;
}

static void	update_redirs_lst(t_list *index, t_param_cmd *param, t_main *main)
{
	t_redir		*redir;
	t_list		*new;
	t_lexer		*lex;
	int			i;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		quit_prog("Fill_struct : redirection part malloc", main);
	lex = index->content;
	redir->type = lex->type;
	redir->fd = ft_atoi_redirection(lex->value, lex->type);
	i = -1;
	while (lex->value[++i])
		if (lex->value[i] == '$')
			redir->var_err = ft_strdup_no_list(lex->value);
	index = index->next;
	lex = index->content;
	redir->file = ft_strdup_no_list(lex->value);
	if (redir->file == NULL)
		quit_prog("Fill_struct : redirection part malloc", main);
	new = ft_lstnew(redir);
	ft_lstadd_back(&param->redir, new);
}

void	fill_struct(t_param_cmd *param, t_main *main)
{
	t_list		*index;
	t_list		*next;
	t_lexer		*tmp;
	int			i;

	i = 0;
	next = NULL;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == COMMAND || tmp->type == ARGUMENT)
			update_command(tmp, param, main);
		// if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
		// 	|| tmp->type == APP_REDIR_OUT || tmp->type == HERE_DOC)
		// 	update_redirs_lst(index, param, main);
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APP_REDIR_OUT)
			update_redirs_lst(index, param, main);
		if (tmp->type == HERE_DOC)
		{
			next = index->next;
			tmp = next->content;
			update_here_doc(tmp->value, param, main);
		}
		index = index->next;
	}
}
