#include "minishell.h"

int	cmd_error(char *cmd, char *error, char *arg, int nbr)
{
	ft_putstr_fd("\033[31mbash_des_freros: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
		ft_putstr_fd(error, 2);
	ft_putstr_fd("\n\033[0m", 2);
	if (nbr)
		errno = nbr;
	return (1);
}
