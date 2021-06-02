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

void	exec_cmd(t_param_cmd *param, t_main *main)
{
	int	i;

	if (!param->cmd[0])
		return ;
	// if (redir->file)
	// {
	// int file = open(redir->file, O_CREAT | O_WRONLY, 0777);
	// int file2 = dup2(file, 1);
// }
	i = 7;
	while (--i >= 0 && ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
		;
	if (!ft_strncmp(param->cmd[0], main->cmd_fct[i].name, 7))
		main->cmd_fct[i].fct(param->cmd + 1, param, main);
	else
		cmd_others(param, main);
	save_last_arg(param->cmd, main);
}

// void	cmd_exec(char **cmd, t_main *main)
// {
// 	int		i;

// 	if (cmd[0] == '\0')
// 		return ;
// 	i = 7;
// 	while (--i >= 0 && ft_strncmp(cmd[0], main->cmd_fct[i].name, 7))
// 		;
// 	if (!ft_strncmp(cmd[0], main->cmd_fct[i].name, 7))
// 		main->cmd_fct[i].fct(cmd + 1, main);
// 	else
// 		cmd_others(cmd, param->redir, main);
// 	save_last_arg(cmd, main);
// }

// void	test_cmd_exec(t_main *main)
// {
// 	char	**tabl;
// 	int		i;

// 	tabl = ft_split(main->line, ' ');
// 	cmd_exec(tabl, main);
// 	i = -1;
// 	while (tabl[++i])
// 		free(tabl[i]);
// 	free(tabl);
// }
