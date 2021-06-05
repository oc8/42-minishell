#include "minishell.h"

static void	update_command(t_lexer *lex, t_param_cmd *param, t_main *main)
{
	char	**new;
	int		i;
	
	i = 0;
	param->n_cmd++;
	new = malloc(sizeof(char*) * (param->n_cmd + 1));
	if (new == NULL)
		quit_prog("Fill_struct : command part malloc", main);
	if (param->cmd)
		while (param->cmd[i])
		{
			new[i] = ft_strdup_no_list(param->cmd[i]);
			if (!new[i++])
				quit_prog("Fill_struct : command part malloc", main);
		}
	new[i] = ft_strdup_no_list(lex->value);
	if (!new[i])
		quit_prog("Fill_struct : command part malloc", main);
	new[++i] = NULL;
	if (param->cmd)	// METTRE DOUBLESTR FREE !!!!!
	{
		i = -1;
		while (param->cmd[++i])
			free(param->cmd[i]);
		free(param->cmd);
		param->cmd = NULL;
	}
	param->cmd = new;
}

static void	update_redirs_lst(t_list *index, t_param_cmd *param, t_main *main)
{
	t_redir		*redir;
	t_list		*new;
	t_lexer		*lex;
	int			i;
	
	redir = ft_calloc(1,sizeof(t_redir));
	if (!redir)
		quit_prog("Fill_struct : redirection part malloc", main);
	// ft_bzero(redir)
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
	// printf("\n\033[31m   lex->value = %s\n   \033[0m", lex->value);
	if (redir->file == NULL)
		quit_prog("Fill_struct : redirection part malloc", main);
	new = ft_lstnew(redir);
	ft_lstadd_back(&param->redir, new);
}

void	fill_struct(t_param_cmd *param, t_main *main)
{
	t_list		*index;
	t_lexer		*tmp;
	int			i;

	i = 0;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == COMMAND || tmp->type == ARGUMENT)
			update_command(tmp, param, main);
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APP_REDIR_OUT)
			update_redirs_lst(index, param, main);
		if (tmp->type == PIPE)
			param->pipe = 1;
		index = index->next;
	}
}
