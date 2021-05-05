#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <sys/errno.h>

# include "libft.h"

// typedef enum	e_error
// {

// }				t_e_error;

typedef struct	s_cmd
{
	char			*line;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_main
{
	t_list	*malloc;
	t_cmd	*cmd;
}				t_main;

#endif
