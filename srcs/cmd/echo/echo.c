#include "minishell.h"

void	cmd_echo(char **arg, t_main *main)
{
	int	i;
	int	flag_n;

	(void)main;
	if (!arg[0])
	{
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
}
