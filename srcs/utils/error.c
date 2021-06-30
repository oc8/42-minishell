#include "minishell.h"

int	cmd_error(char *cmd, char *error, char *arg, int nbr)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
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
	ft_putstr_fd("\n", STDERR_FILENO);
	g_global.exit_status = nbr;
	return (nbr);
}

void	prog_error(char *cmd, char *error, char *errorstr)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error)
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (errorstr)
		ft_putstr_fd(errorstr, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_global.exit_status = 0;
}
