#include "minishell.h"

void	cmd_cd(char **arg, t_main *main)
{
	(void)main;

	if (!ft_strncmp(arg[0], ".", 2))
		return ;
	if (chdir(arg[0]) == -1)
		// quit_prog("chdir() on cd", main);
		printf("\033[31mbash_des_freros: cd: %s: No such file or directory\n", arg[0]);
}
