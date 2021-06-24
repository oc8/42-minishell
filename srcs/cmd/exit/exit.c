#include "minishell.h"

static int	is_nbr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	cmd_exit(t_param_cmd *param, t_main *main)
{
	unsigned char	status;
	char			**arg;

	arg = param->cmd + 1;
	printf("exit\n");
	if (!arg[0])
		status = 0;
	else if (!is_nbr(arg[0]))
	{
		cmd_error("exit", "numeric argument required", arg[0], 255);
	}
	else if (arg[1])
	{
		cmd_error("exit", "too many arguments", 0, 1);
		loop(main);
	}
	else
	{
		status = ft_atoi(arg[0]);
	}
	main->exit_status = status;
	free_all(main);
	exit(status);
}
