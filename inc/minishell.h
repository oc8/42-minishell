#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
// # include <termios.h>

# include "libft.h"

# define PWD_MAX_SIZE 256

typedef enum e_caracter_lex
{
	WORD_NOT_FINISHED,
	SPACE_C,
	WORD_FINISHED,
	LINE_FINISHED
}				t_caracter_lex;

typedef enum e_type_lex
{
	VAR_ENV,
	TO_DEFINE,
	COMMAND,
	ARGUMENT,
	REDIR_IN,
	APP_REDIR_OUT,
	REDIR_OUT,
	HERE_DOC,
	FILE_N,
	PIPE,
	NEW_COMMAND,
}				t_type_lex;

typedef enum e_index_cmd
{
	I_ECHO,
	I_PWD,
	I_CD,
	I_ENV,
	I_EXPORT,
	I_UNSET,
	I_EXIT
}				t_index_cmd;

typedef struct s_utils_lexer
{
	char	*str;
	char	*word;
	int		i;
	int		sing_q;
	int		double_q;
	int		echap;
	int		i_lst;
	int		var_env;
	int		start_word;
}				t_utils_lexer;

typedef struct s_lexer
{
	t_type_lex		type;
	char			*value;
}				t_lexer;

typedef struct s_utils_var
{
	t_list		*index;
	t_list		*previous;
	t_list		*next;
	t_lexer		*tmp;
	t_lexer		*tmp2;
	char		*str_with_var;
	char		*new;
	t_lexer		*tmp3;
	t_list		*save;
	t_list		*last;
}				t_utils_var;

typedef struct s_redir
{
	int			fd;
	char		*file;
	t_type_lex	type;
	char		*var_err;
	// int			pipefd[2];
	char		*buff;
}				t_redir;

typedef struct s_param_cmd
{
	char	**cmd;
	t_list	*redir;
	int		pipe_before;
	int		pipe_after;
	int		n_cmd;
	// int		flag_in_file;
	char	*here_doc_str;
	int		file_fd_out[2];
	int		file_fd_in[2];
}				t_param_cmd;

struct			s_main;

typedef void	(*t_fct_cmd)(t_param_cmd *, struct s_main *);

typedef struct s_function
{
	t_fct_cmd		fct;
	char			*name;
}				t_function;

typedef struct s_main
{
	char			*line;
	char			**env;
	size_t			nbr_env;
	t_list			*lexer;
	// t_list			*histo;
	t_list			*free;
	t_function		cmd_fct[7];
	pid_t			pid[10];
	int				pid_nbr;
	int				file;
	int				save_fd[2];
	int				pipefd[2][2];
	int				pipefd_here_doc[2];
	int				count;
	char			*home_path;
}				t_main;

typedef struct	s_global
{
	t_main	*main; // ?
	int		exit_status;
	int		pid;
	t_list	*free;
	t_list	*fd_open;
}				t_global;

t_global	global;

// t_main	main;

void	loop(t_main *main);

t_main	res;

/*
**	-->	PARSING <--
*/
void	get_operator_command(t_main *main);
void	tokenization(char *str, int indice, t_main *main);
void	update_word(char c, char **str);
void	predefine_var(t_utils_lexer *utils, t_main *m);
void	check_caracter_var(t_utils_lexer *utils, t_main *main);
void	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main);
void	backslash(char c, t_utils_lexer *utils, t_main *main);
void	single_quotes(char c, t_utils_lexer *utils, t_main *main);
void	double_quotes(char c, t_utils_lexer *utils, t_main *main);
void	dollar(char c, t_utils_lexer *utils, t_main *m);
void	malloc_element(t_type_lex type, t_utils_lexer *utils, t_main *main);
void	verify_syntax(t_utils_lexer *utils, t_main *main);
void	update_main_lexer(t_type_lex type, t_list **save);
int		verif_redir_var(t_lexer *to_check, t_list *prec, t_main *main);
void	reconize_primitive_type(t_lexer *lex, t_utils_lexer *utils, t_main *m);
void	create_param_cmd(t_list **param_lst, t_main *main);
void	treat_here_doc_line(char **new, char *str, t_main *main);
void	remplace_var_value(char **new, char *str, t_main *main);
void	define_text_types(t_main *main);
void	fill_struct(t_param_cmd *param, t_main *main);
void	print_struct_cmd(t_list *param);

/*
**	-->	CMD <--
*/
void	cmd_others(t_param_cmd *param, t_main *main);
// void	cmd_exec(t_param_cmd *param, t_main *main);
void	cmd_exec(t_list *param_lst, t_main *main);
void	cmd_call(t_param_cmd *param, t_main *main);
void	cmd_echo(t_param_cmd *param, t_main *main);
void	cmd_pwd(t_param_cmd *param, t_main *main);
void	cmd_env(t_param_cmd *param, t_main *main);
void	cmd_export(t_param_cmd *param, t_main *main);
void	cmd_unset(t_param_cmd *param, t_main *main);
void	cmd_cd(t_param_cmd *param, t_main *main);
void	cmd_exit(t_param_cmd *param, t_main *main);
// void	test_cmd_exec(t_main *main); // temp

/*
**	-->	REDIR <--
*/
void	open_fd(t_param_cmd *param, t_main *main);
void	redir_in(int fd[2], t_main *main);
void	redir_out(int fd[2], t_main *main);
void	here_doc(char *str, t_main *main);
void	redir_pipe_before(t_param_cmd *param, t_main *main);
void	redir_pipe_after(t_param_cmd *param, t_main *main);
void	save_here_doc(t_list *param_lst, t_main *main);
void	open_fd_out(int fd[2], t_redir *redir, t_main *main);
void	open_fd_in(int fd[2], t_redir *redir, t_main *main);
void	set_pipe(t_param_cmd *param, t_list *param_lst, t_main *main);
void	close_pipe(t_main *main);
// void	check_fd(t_param_cmd *param, t_main *main);

/*
**	-->	UTILS <--
*/
void	print_prompt();
void	quit_prog(char *error_str, t_main *main);
char	*save_path_home(char **env, t_main *main);
char	**cpy_env(char *env[], t_main *main);
void	free_all(t_main *main);
int		ft_strncmp_minishell(const char *s1, const char *s2, size_t n);
char	*ft_strdup_no_list(const char *s1);
int		ft_atoi_redirection(const char *nptr, t_type_lex type);
void	free_lexer(void *s);
void	free_param_cmd(void *ptr);
void	init_cmd_fct(t_main *main);
char	**split_var(char *var, t_main *main);
int		cmd_error(char *cmd, char *error, char *arg, int nbr);
int		check_var_name(char *name);
int		var_defined(char *var, t_main *main);
void	new_var(char *add, t_main *main);
void	edit_var(char *add, size_t i, t_main *main);
void	print_lexer(t_main *main);
void	redirection(t_param_cmd *param, t_main *main);
void	del_var(int index, t_main *main);
int		is_here_doc(t_main *main);
int		error_syntax(char *str, t_main *main);
void	reset_var(t_main *main);

#endif
