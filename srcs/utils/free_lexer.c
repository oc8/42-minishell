#include "minishell.h"

void	free_lexer(void *s)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)s;
	free(lexer->value);
	free(lexer);
}
