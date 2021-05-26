#include "minishell.h"

void	cmd_cd(char **arg, t_main *main)
{
	(void)main;

	if (!ft_strncmp(arg[0], ".", 2))
		return ;
	if (chdir(arg[0]) == -1)
		// quit_prog("chdir() on cd", main);
		cmd_error("cd", "No such file or directory", arg[0], 1);
}
