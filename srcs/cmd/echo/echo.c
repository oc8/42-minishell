#include "minishell.h"

void	cmd_echo(t_param_cmd *param, t_main *main)
{
	int		i;
	int		j;
	int		flag_n;
	char	**arg;

	arg = param->cmd + 1;
	if (!arg[0])
	{
		printf("\n");
		return ;
	}
	flag_n = 0;
	j = 0;
	while (arg[j][0] == '-')
	{
		i = 0;
		while (arg[j][++i] == 'n')
			;
		if (i > 1 && !arg[j][i])
		{
			flag_n = 1;
			j++;;
		}
		else
		{
			j--;
			break ;
		}
	}
	while (arg[j])
	{
		printf("%s", arg[j++]);
		if (arg[j])
			printf(" ");
	}
	if (!flag_n)
		printf("\n");
}
