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
	OPERATOR,
	ARGUMENT,
	FILE_NAME
}				t_type_lex;

typedef enum	e_type_cmd
{
	ECHO_CMD,
	PWD_CMD,
	CD_CMD,
	ENV_CMD,
	EXPORT_CMD,
	UNSET_CMD,
	EXIT_CMD

}				t_type_cmd;

struct s_main;

typedef void	(*t_fct_cmd)(char **, struct s_main *);

typedef struct	s_function
{
	t_fct_cmd		fct;
	int				cmd;
}				t_function;

typedef struct	s_utils_lexer
{
	int		i;
	int		w_count;
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
	t_list			*lexer;
	t_list			*histo;
	t_list			*free;
	t_function		cmd_fct[7];
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
void	cmd_exec(int cmd, char **arg, t_main *main);
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

#endif
