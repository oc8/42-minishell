#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <limits.h>
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
	VAR_ENV,
	TO_DEFINE,
	COMMAND,
	ARGUMENT,
	REDIR_INPUT,
	APPEND_REDIR_OUTPUT,
	REDIR_OUTPUT,
	FILE_NAME,
	PIPE,
	NEW_COMMAND,
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
	char	*str;
	char	*word;
	int		i;
	int		sing_q;
	int		double_q;
	int		echap;
	int		i_lst;
	int		var_env;
}				t_utils_lexer;

typedef struct	s_lexer
{
	t_type_lex		type;
	char			*value;
}				t_lexer;

typedef struct	s_var_info
{
	int		i_lst;
	char	*value;
}				t_var_info;

typedef struct	s_redir
{
	int		fd;
	char	*file;
	char	*var_err;
}				t_redir;

typedef struct	s_param_cmd
{
	char	**cmd;
	t_redir	redir_in;
	t_redir	*redir_out;
	t_redir	*app_redir_out;
	int		pipe;
	int		n_cmd;
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
void	tokenization(char *str, int indice, t_main *main);
void	update_word(char c, t_utils_lexer *utils, t_main *main);
void	predefine_var(t_utils_lexer *utils, t_main *m);
void	check_caracter_var(t_utils_lexer *utils, t_main *main);
void	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main);
void	malloc_element(t_type_lex type, t_utils_lexer *utils, t_main *main);
void	verify_syntax(t_utils_lexer *utils, t_main *main);
void	reconize_primitive_type(t_lexer *lex, t_utils_lexer *utils, t_main *m);
void	create_param_cmd(t_param_cmd *param, t_main *main);
void	define_text_types(t_main *main);
void	fill_struct(t_param_cmd *param, t_main *main);
void	print_struct_cmd(t_param_cmd *param);

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
int		cmd_error(char *cmd, char *error, char *arg);
void	print_lexer(t_main *main);

#endif
