#include "minishell.h"

void	init_term(t_main *main)
{
	char	*term_type = getenv("TERM");

	if (!term_type)
		quit_prog("TERM must be set (see 'env')", main);
	if (tgetent(NULL, term_type) < 1)
		quit_prog("Could not access to the termcap database", main);

// char* color_cap = tgetstr("AF", NULL);
// tputs(tparm(color_cap, COLOR_GREEN), 1, putchar);
// char *cm_cap = tgetstr("cm", NULL);
// tputs(tgoto(cm_cap, 5, 5), 1, putchar);
}
