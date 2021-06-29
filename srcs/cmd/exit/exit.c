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

static long long	ft_atoi_exit(const char *str, unsigned char *status)
{
	long long	rs;
	int			i;
	int			neg;

	neg = 1;
	rs = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		rs = rs * 10 + (str[i++] - '0');
	if (rs < 0)
		*status = 255;
	return (rs * neg);
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
		rs = ft_atoi_exit(arg[0], &status);
		if (ft_strlen(&arg[0][i]) > 19 || status == 255)
			status = cmd_error("exit", "numeric argument required", arg[0], 255);
		else
			status = (unsigned char)rs;
	}
	free_all(main);
	exit(status);
}
