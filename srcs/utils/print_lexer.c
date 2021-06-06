#include "minishell.h"

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
		if (tmp->type == COMMAND)
			printf("Type = COMMAND\n");
		else if (tmp->type == ARGUMENT)
			printf("Type = ARGUMENT\n");
		else if (tmp->type == NEW_COMMAND)
			printf("Type = NEW_COMMAND\n");
		else if (tmp->type == FILE_N)
			printf("Type = FILE_N\n");
		else if (tmp->type == REDIRECTION)
			printf("Type = REDIRECTION\n");
		else if (tmp->type == TO_DEFINE)
			printf("Type = TO_DEFINE\n");
		else if (tmp->type == VAR_ENV)
			printf("Type = VAR_ENV\n");
		else if (tmp->type == PIPE)
			printf("Type = PIPE\n");
		else if (tmp->type == REDIR_OUT)
			printf("Type = REDIR_OUT\n");
		else if (tmp->type == APP_REDIR_OUT)
			printf("Type = APP_REDIR_OUT\n");
		else if (tmp->type == REDIR_IN)
			printf("Type = REDIR_IN\n");
		printf("\n");
		iter = iter->next;
	}
}