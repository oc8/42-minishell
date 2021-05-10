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

typedef enum	e_type_lex
{
	COMMAND,
	ARGUMENT,
	OPERAND
}				t_type_lex;

typedef struct	s_lexer
{
	char			*type;
	char			*value;
}				t_lexer;

typedef struct	s_main
{
	char			*line;
	t_list			*lexer;
	t_list			*histo;
	t_list			*free;
}				t_main;

/*
**	-->	PARSING <--
*/
void	get_operator_command(t_main *main);

/*
**	-->	CMD <--
*/
void	cmd_exec(t_main *main);
int		cmd_echo(char **arg);

/*
**	-->	UTILS <--
*/
void	fail(char *error_str, t_main *main);
int		ft_strncmp_minishell(const char *s1, const char *s2, size_t n);

#endif
