#include "minishell.h"

static int	verify_new_command(int i, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	
	if (i == 0)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	index = main->lexer;
	while (--i > 0)
		index = index->next;
	tmp = index->content;
	if (tmp->type == NEW_COMMAND)
	{
		printf("bash: syntax error near unexpected token `%s'\n", tmp->value);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	return (1);
}

int	verify_redirection_var(t_lexer *to_check, t_list *prec, t_main *main)
{
	char	*new;
	t_lexer	*tmp;
	int		i;

	new = NULL;
	remplace_var_value(&new, to_check->value, main);
	// printf("to_check->value = |%s|, new = %s\n", to_check->value, new);
	i = -1;
	if (new)
		while (new[++i])
			if (new[i] == ' ')
			{
				tmp = prec->content;
				free(tmp->value);
				tmp->value = NULL;
				tmp->value = ft_strdup_no_list(to_check->value);
				free(new);
				return (-1);
			}
	free(new);
	return (1);
}

static int	verify_redirection(int i, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_list	*prec;
	t_lexer	*tmp;
	
	if (i == ft_lstsize(main->lexer) - 1)
	{
		printf("bash: syntax error near unexpected token `nexline'\n");
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	index = main->lexer;
	while (--i >= 0)
		index = index->next;
	prec = index;
	index = index->next;
	tmp = index->content;
	if (tmp->type != TO_DEFINE && tmp->type != FILE_NAME && tmp->type != VAR_ENV)
	{
		printf("bash: syntax error near unexpected token `%s'\n", tmp->value);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	// if (tmp->type == VAR_ENV && verify_redirection_var(tmp, prec, main) == -1)
	// 	return (-1);
	return (1);
}

void	verify_syntax(t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int		i;
	
	if (utils->echap || utils->double_q || utils->sing_q)
	{
		printf("Error : Multiline is not accepted\n");
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
	}
	i = 0;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if ((tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APP_REDIR_OUT)
			&& verify_redirection(i, utils, main) == -1)
				return ;
		else if (tmp->type == NEW_COMMAND
			&& verify_new_command(i, utils, main) == -1)
				return ;
		index = index->next;
		i++;
	}
}
