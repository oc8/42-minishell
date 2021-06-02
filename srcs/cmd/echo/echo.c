#include "minishell.h"

void	cmd_echo(t_param_cmd *param, t_main *main)
{
	int	i;
	int	flag_n;
	int	file2;
	char	**arg;

	arg = param->cmd + 1;
	if (param->redir)
		file2 = redirection(param->redir, main);
	if (!arg[0])
	{
		if (param->redir)
		close(file2);
		printf("\n");
		return ;
	}
	flag_n = 0;
	i = 0;
	if (arg[0][0] == '-')
		while (arg[0][++i] == 'n')
			;
	if (i > 1 && !arg[0][i])
	{
		flag_n = 1;
		i = 1;
	}
	else
		i = 0;
	while (arg[i])
	{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
	}
	if (!flag_n)
		printf("\n");
	if (param->redir)
		close(file2);
}
