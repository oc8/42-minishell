#include "minishell.h"

int	cmd_error(char *cmd, char *error, char *arg, int nbr)
{
	ft_putstr_fd("\033[31mbash: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n\033[0m", STDERR_FILENO);
	global.exit_status = nbr;
	return (nbr);
}
