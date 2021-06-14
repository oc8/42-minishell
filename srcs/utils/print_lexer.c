#include "minishell.h"

static void	print_lexer_type(t_type_lex type)
{
	if (type == COMMAND)
		printf("Type = COMMAND\n");
	else if (type == ARGUMENT)
		printf("Type = ARGUMENT\n");
	else if (type == NEW_COMMAND)
		printf("Type = NEW_COMMAND\n");
	else if (type == FILE_N)
		printf("Type = FILE_N\n");
	else if (type == TO_DEFINE)
		printf("Type = TO_DEFINE\n");
	else if (type == VAR_ENV)
		printf("Type = VAR_ENV\n");
	else if (type == PIPE)
		printf("Type = PIPE\n");
	else if (type == REDIR_OUT)
		printf("Type = REDIR_OUT\n");
	else if (type == APP_REDIR_OUT)
		printf("Type = APP_REDIR_OUT\n");
	else if (type == REDIR_IN)
		printf("Type = REDIR_IN\n");
	else if (type == HERE_DOC)
		printf("Type = HERE_DOC\n");
}

void	print_lexer(t_main *main)
{
	t_lexer	*tmp;
	t_list	*iter;
	
	printf("Lexer , size = %d : \n", ft_lstsize(main->lexer));
	iter = main->lexer;
	while (iter != NULL)
	{
		tmp = iter->content;
		printf("Value = |%s|\n", tmp->value);
		print_lexer_type(tmp->type);
		printf("\n");
		iter = iter->next;
	}
}