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
		ft_putstr_fd("\n", 1);
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
		// dprintf(2, "%s\n", arg[j++]);
		ft_putstr_fd(arg[j], 1);
		// printf("%s", arg[j]);
		j++;
		if (arg[j])
			ft_putstr_fd(" ", 1);
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
}
