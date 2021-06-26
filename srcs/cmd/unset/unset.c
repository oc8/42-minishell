#include "minishell.h"

void	cmd_unset(t_param_cmd *param, t_main *main)
{
	size_t	i;
	int		index;
	char	**arg;

	arg = param->cmd + 1;
	if (!arg[0])
		return ;
	i = 0;
	while (arg[i])
	{
		if (check_var_name(arg[i]) != 2)
			main->exit_status = cmd_error("export", "not a valid identifier", arg[i], 1);
		index = var_defined(arg[i], main);
		if (index > -1)
			del_var(index, main);
		i++;
	}
}
