#include "minishell.h"

int	cmd_error(char *cmd, char *error, char *arg)
{
	printf("\033[31mbash_des_freros: ");
	if (cmd)
		printf("%s: ", cmd);
	if (arg)
		printf("`%s': ", arg);
	if (error)
		printf("%s: ", error);
	printf("\n\033[0m");
	return (1);
}
