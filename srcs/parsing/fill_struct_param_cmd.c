#include "minishell.h"

static void	update_here_doc(char *end, t_param_cmd *param, t_main *main)
{
	t_utils_heredoc	u;

	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&u, sizeof(t_utils_heredoc));
	u.here_doc = ft_strdup_no_list("");
	while (ft_strncmp_minishell(u.new_line, end, -1))
	{
		free(u.new_line);
		u.new_line = NULL;
		u.new_line = readline("> ");
		if (!u.new_line)
			u.new_line = ft_strdup_no_list(end);
		if (ft_strncmp_minishell(u.new_line, end, -1))
		{
			treat_here_doc_line(&u.with_var, u.new_line, main);
			if (u.with_var)
				u.here_doc = strjoin_here_doc_parsing(&u.here_doc, &u.with_var);
			free(u.with_var);
			u.with_var = NULL;
		}
	}
	free(u.new_line);
	free(param->here_doc_str);
	param->here_doc_str = u.here_doc;
	signal(SIGQUIT, &sig_action);
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
