#include "minishell.h"

void	save_last_arg(char **cmd, t_main *main)
{
	size_t	i;
	int		index;
	char	*tmp;

	i = 0;
	while (cmd[i])
		i++;
	if (!i)
		return ;
	index = var_defined("_", main);
	if (index > -1)
		edit_var(cmd[i - 1], index, main);
	else
	{
		tmp = ft_strjoin("_=", cmd[i - 1]);
		new_var(tmp, main);
		free(tmp);
	}
}

void	exec_cmd(t_param_cmd *cmd, t_main *main)
{
	int	i;

	if (!cmd->cmd[0])
		return ;
	i = 7;
	while (--i >= 0 && ft_strncmp(cmd->cmd[0], main->cmd_fct[i].name, 7))
		;
	if (!ft_strncmp(cmd->cmd[0], main->cmd_fct[i].name, 7))
		main->cmd_fct[i].fct(cmd->cmd + 1, main);
	else
		cmd_others(cmd->cmd, main);
<<<<<<< HEAD
	save_last_arg(cmd->cmd, main);
=======
	// save_last_arg(cmd, main);
>>>>>>> 18c920bfe5a0b297d98d8280df0aa3f022b9eff2
}

void	cmd_exec(char **cmd, t_main *main)
{
	int		i;

	if (cmd[0] == '\0')
		return ;
	i = 7;
	while (--i >= 0 && ft_strncmp(cmd[0], main->cmd_fct[i].name, 7))
		;
	if (!ft_strncmp(cmd[0], main->cmd_fct[i].name, 7))
		main->cmd_fct[i].fct(cmd + 1, main);
	else
		cmd_others(cmd, main);
	save_last_arg(cmd, main);
}

void	test_cmd_exec(t_main *main)
{
	char	**tabl;
	int		i;

	tabl = ft_split(main->line, ' ');
	cmd_exec(tabl, main);
	i = -1;
	while (tabl[++i])
		free(tabl[i]);
	free(tabl);
}
