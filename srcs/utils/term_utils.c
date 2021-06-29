#include "minishell.h"

void	init_term(t_main *main)
{
	char	*term_type;

	term_type = getenv("TERM");
	if (!term_type)
		quit_prog("TERM must be set (see 'env')", main);
	if (tgetent(NULL, term_type) < 1)
		quit_prog("Could not access to the termcap database", main);
}
