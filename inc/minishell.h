#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <sys/errno.h>

# include "libft.h"

# define PWD_MAX_SIZE 256

// typedef enum	e_error
// {

// }				t_e_error;

typedef enum	e_caracter_lex
{
	WORD_NOT_FINISHED,
	SPACE,
	WORD_FINISHED,
	LINE_FINISHED
}				t_caracter_lex;

typedef enum	e_type_lex
{
	COMMAND,
	ARGUMENT,
	NEW_COMMAND,
	REDIRECTION,
	FILE_NAME
}				t_type_lex;

struct s_main;

typedef void	(*t_fct_cmd)(char **, struct s_main *);

typedef struct	s_function
{
	t_fct_cmd		fct;
	char			*name;
}				t_function;

typedef struct	s_utils_lexer
{
	char	*word;
	int		i;
	int		sing_q;
	int		double_q;
	int		echap;
}				t_utils_lexer;

typedef struct	s_lexer
{
	int		type;
	char	*value;
}				t_lexer;

typedef struct	s_main
{
	char			*line;
	char			**env;
	size_t			nbr_env;
	t_list			*lexer;
	t_list			*histo;
	t_list			*free;
	t_function		cmd_fct[7];
}				t_main;

void	loop(t_main *main);

/*
**	-->	PARSING <--
*/
void	get_operator_command(t_main *main);
void	pars_line(t_main *main);
void	lexer(t_main *main);
void	update_word(char c, t_utils_lexer *utils, t_main *main);
void	check_local_var(t_utils_lexer *utils, t_main *main);
void	reconize_type(const char *elem, t_lexer *lexer, t_main *main);

/*
**	-->	CMD <--
*/
void	cmd_others(char **arg, t_main *main);
void	cmd_exec(char **arg, t_main *main);
void	cmd_echo(char **arg, t_main *main);
void	cmd_pwd(char **arg, t_main *main);
void	cmd_env(char **arg, t_main *main);
void	cmd_export(char **arg, t_main *main);
void	cmd_unset(char **arg, t_main *main);
void	cmd_cd(char **arg, t_main *main);
void	cmd_exit(char **arg, t_main *main);
void	test_cmd_exec(t_main *main); // temp

/*
**	-->	UTILS <--
*/
void	quit_prog(char *error_str, t_main *main);
int		ft_strncmp_minishell(const char *s1, const char *s2, size_t n);
char	*ft_strdup_no_list(const char *s1);
void	free_lexer(void *s);
void	init_cmd_fct(t_main *main);
char	**split_var(char *var);

#endif
