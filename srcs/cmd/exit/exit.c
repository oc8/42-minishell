#include "minishell.h"

void	cmd_exit(t_param_cmd *param, t_main *main)
{
	printf("exit\n");
	quit_prog(0, main);
}
