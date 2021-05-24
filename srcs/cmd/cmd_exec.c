#include "minishell.h"

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
