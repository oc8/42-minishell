#include "minishell.h"

int	is_here_doc(t_main *main)
{
	t_list	*last;
	t_lexer	*tmp;

	last = ft_lstlast(main->lexer);
	tmp = last->content;
	if (tmp->type == HERE_DOC)
		return (TRUE);
	return (FALSE);
}
