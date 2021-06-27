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
	long long		rs;
	char			**arg;
	size_t			i;

	arg = param->cmd + 1;
	if (!param->pipe_after && !param->pipe_before)
		printf("exit\n");
	status = 0;
	i = 0;
	if (arg[0] && arg[0][i] == '-')
		i++;
	if (!arg[0])
		;
	else if (!is_nbr(&arg[0][i]))
		cmd_error("exit", "numeric argument required", arg[0], 255);
	else if (arg[1])
	{
		cmd_error("exit", "too many arguments", 0, 1);
		loop(main);
	}
	else
	{
		rs = ft_atoi_ll(arg[0]);
		printf("rs = %lld\n", rs);
		if (ft_strlen(&arg[0][i]) > 19 || rs > LONG_MAX || rs < LONG_MIN) // error "exit 9223372036854775808"
			status = cmd_error("exit", "numeric argument required", arg[0], 255);
		else
			status = (unsigned char)rs;
	}
	
	free_all(main);
	exit(status);
}
