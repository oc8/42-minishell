#include "minishell.h"

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
	
	// char	**last_arg;

	// i = 0;
	// while (cmd[i])
	// 	i++;
	// last_arg = ft_calloc(2, sizeof(char *));
	// last_arg[0] = ft_strjoin("_=", cmd[i - 1]);
	// last_arg[1] = 0;
	// main->cmd_fct[4].fct(last_arg, main);
	// ft_freedoublestr(&last_arg);
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
