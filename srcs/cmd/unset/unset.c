#include "minishell.h"

void	cmd_unset(t_param_cmd *param, t_main *main)
{
	size_t	i;
	int		index;
	char	**arg;
	int		file2;

	arg = param->cmd + 1;
	if (param->redir)
		file2 = redirection(param->redir, main);
	if (param->redir)
		close(file2);
	if (!arg[0])
		return ;
	i = 0;
	while (arg[i])
	{
		if (check_var_name(arg[i]) != 2)
			cmd_error("export", "not a valid identifier", arg[i], 1);
		index = var_defined(arg[i], main);
		if (index > -1)
			del_var(index, main);
		i++;
	}
}
