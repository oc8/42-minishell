#include "minishell.h"

static int	first_command(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;

	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == COMMAND)
			return (FALSE);
		index = index->next;
	}
	return (TRUE);
}

static int	redirection_file(int i, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;

	if (i == 0)
		return (FALSE);
	index = main->lexer;
	while (--i > 0)
		index = index->next;
	tmp = index->content;
	if (tmp->type == REDIR_OUT || tmp->type == REDIR_IN
		|| tmp->type == APP_REDIR_OUT || tmp->type == HERE_DOC)
		return (TRUE);
	else
		return (FALSE);
}

void	define_text_types(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int		i;

	i = 0;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == TO_DEFINE)
		{
			if (redirection_file(i, main) == TRUE)
				tmp->type = FILE_N;
			else if (first_command(main) == TRUE)
				tmp->type = COMMAND;
			else
				tmp->type = ARGUMENT;
		}
		index = index->next;
		i++;
	}
}

void	reconize_primitive_type(t_lexer *lex, t_utils_lexer *utils)
{
	int	i;

	if (utils->var_env == 1)
	{
		free(lex->value);
		lex->value = NULL;
		i = utils->start_word;
		while (i < utils->i)
			update_word(utils->str[i++], &lex->value);
		lex->type = VAR_ENV;
		utils->var_env = 0;
		if (utils->double_q == 1)
			utils->double_q = 0;
	}
	else
		lex->type = TO_DEFINE;
}
