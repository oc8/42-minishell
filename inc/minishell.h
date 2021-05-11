#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <sys/errno.h>

# include "libft.h"

# define PWD_MAX_SIZE 256

// typedef enum	e_error
// {

// }				t_e_error;

typedef enum	e_type_lex
{
	COMMAND,
	OPERATOR,
	ARGUMENT,
	FILE_NAME
}				t_type_lex;

typedef struct	s_lexer
{
	int		type;
	char	*value;
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
void	pars_line(t_main *main);
void	lexer(t_main *main);

/*
**	-->	CMD <--
*/
void	cmd_exec(t_main *main);
int		cmd_echo(char **arg);
void	cmd_exit(t_main *main);
void	cmd_pwd(t_main *main);
void	cmd_cd(t_main *main, char **arg);

/*
**	-->	UTILS <--
*/
void	quit_prog(char *error_str, t_main *main);
int		ft_strncmp_minishell(const char *s1, const char *s2, size_t n);
char	*ft_strdup_no_list(const char *s1);
void	free_lexer(void *s);

#endif
