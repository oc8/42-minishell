#include "minishell.h"

int	error_syntax(char *str, t_main *main)
{
	int		fd_int;
	char	*fd_str;

	if (!ft_isdigit(str[0]))
		printf("bash: syntax error near unexpected token `%s'\n", str);
	else
	{
		fd_int = ft_atoi(str);
		fd_str = ft_itoa(fd_int);
		printf("bash: syntax error near unexpected token `%s'\n", fd_str);
		free(fd_str);
	}
	g_global.exit_status = 2;
	ft_lstclear(&main->lexer, free_lexer);
	return (-1);
}
