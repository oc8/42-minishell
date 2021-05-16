#include "minishell.h"

void	cmd_others(char **arg, t_main *main)
{
	printf("%d\n", execve("ping", "youtube.com", "ping"));
}
