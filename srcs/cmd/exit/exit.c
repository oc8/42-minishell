#include "minishell.h"

void	cmd_exit(char **arg, t_main *main)
{
	(void)arg;
	printf("exit\n");
	quit_prog(0, main);
}
