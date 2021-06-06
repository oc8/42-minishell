#include "minishell.h"

static int	verif_newcmd(int i, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	
	if (i == 0)
		return (error_syntax(";", main));
	index = main->lexer;
	while (--i > 0)
		index = index->next;
	tmp = index->content;
	if (tmp->type != TO_DEFINE && tmp->type != FILE_N && tmp->type != VAR_ENV
		&& tmp->type != COMMAND && tmp->type != ARGUMENT)
		return (error_syntax(";", main));
	return (1);
}

int	verif_redirection_var(t_lexer *to_check, t_list *prec, t_main *main)
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

static int	verif_redir(int i, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_list	*prec;
	t_lexer	*tmp;
	
	if (i == ft_lstsize(main->lexer) - 1)
		return (error_syntax("newline", main));
	index = main->lexer;
	while (--i >= 0)
		index = index->next;
	prec = index;
	index = index->next;
	tmp = index->content;
	if (tmp->type != TO_DEFINE && tmp->type != FILE_N && tmp->type != VAR_ENV)
		return (error_syntax(tmp->value, main));
	return (1);
}

static int	verif_pipe(int i, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	// t_list	*prec;
	t_lexer	*tmp;
	
	if (i == ft_lstsize(main->lexer) - 1)
	{
		printf("Error : Multiline is not accepted\n");
		ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	else if (i == 0)
		return (error_syntax("|", main));
	index = main->lexer;
	while (--i > 0)
		index = index->next;
	// prec = index;
	// index = index->next;
	tmp = index->content;
	if (tmp->type != TO_DEFINE && tmp->type != FILE_N && tmp->type != VAR_ENV
		&& tmp->type != COMMAND && tmp->type != ARGUMENT)
		return (error_syntax("|", main));
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
		ft_lstclear(&main->lexer, free_lexer);
	}
	i = 0;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if ((tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APP_REDIR_OUT) && verif_redir(i, utils, main) == -1)
				return ;
		else if (tmp->type == NEW_COMMAND && verif_newcmd(i, utils, main) == -1)
				return ;
		else if (tmp->type == PIPE && verif_pipe(i, utils, main) == -1)
				return ;
		index = index->next;
		i++;
	}
}
