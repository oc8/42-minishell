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

// typedef struct	s_cmd
// {
// 	char			*line;
// 	struct s_cmd	*next;
// }				t_cmd;

// typedef struct	s_main
// {
// 	t_list	*malloc;
// 	t_cmd	*cmd;
// }				t_main;

// typedef struct	s_histo
// {
// 	char			*line;
// 	struct s_histo	*next;
// }				t_histo;

typedef struct	s_res
{
	char			*line;
	t_list			*histo;
	t_list			*free;
}				t_res;


// -->  PARSING  <--
void	get_operator_command(t_res *res);

// -->  UTILS  <--
void	fail(char *error_str, t_res *res);
int		ft_strncmp_minishell(const char *s1, const char *s2, size_t n);

#endif
