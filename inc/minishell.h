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

typedef enum	e_caracter_lex
{
	WORD_NOT_FINISHED,
	SPACE,
	WORD_FINISHED,
	LINE_FINISHED
}				t_caracter_lex;

typedef enum	e_type_lex
{
	REDIRECTION,
	NEW_COMMAND,
	VAR_ENV,
	TO_DEFINE,
	COMMAND,
	ARGUMENT,
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	APPEND_REDIRECTION_OUTPUT,
	PIPE,
	FILE_NAME,
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
	int		var_env;
}				t_utils_lexer;

typedef struct	s_lexer
{
	t_type_lex		type;
	char			*value;
}				t_lexer;

typedef struct	s_redir
{
	int		fd;
	char	*file;
	char	*var_err;
}				t_redir;

typedef struct	s_param_cmd
{
	char	**cmd;
	t_redir	input_redir;
	t_redir	*output_redir;
	t_redir	*append_output_redir;
	int		pipe;
}				t_param_cmd;

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
void	tokenization(t_main *main);
void	update_word(char c, t_utils_lexer *utils, t_main *main);
void	predefine_var(t_utils_lexer *utils, t_main *m);
void	check_local_var(t_utils_lexer *utils, t_main *main);
void	verify_syntax(t_utils_lexer *utils, t_main *main);
void	reconize_primitive_type(t_lexer *lex, t_utils_lexer *utils, t_main *m);
void	reconize_type(t_lexer *lex, t_utils_lexer *utils, t_main *m);
void	create_param_cmd(t_param_cmd *param, t_main *main);

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
char	**split_var(char *var, t_main *main);
int		cmd_error(char *cmd, char *error, char *arg, int nbr);
int		check_var_name(char *name);
int		var_defined(char *var, t_main *main);
void	new_var(char *add, t_main *main);
void	edit_var(char *add, size_t i, t_main *main);

#endif
