#include "minishell.h"

static void	change_var(int lvl, int i, t_main *main)
{
	if (lvl < 1000)
		edit_var(ft_itoa(lvl), i, main);
	else if (lvl == 1000)
	{
		del_var(i, main);
		new_var("SHLVL=", main);
	}
	else
	{
		del_var(i, main);
		new_var("SHLVL=1", main);
		ft_putstr_fd("bash: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(lvl, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
	}
}

static void	inc_shlvl(t_main *main)
{
	char	**var;
	int		i;
	int		lvl;

	i = var_defined("SHLVL", main);
	if (i > -1)
	{
		var = split_var(main->env[i], main);
		// printf("%s", var[0]);
		lvl = ft_atoi(var[1]);
		ft_freedoublestr(&var);
		lvl++;
		change_var(lvl, i, main);
	}
	else
		new_var("SHLVL=1", main);
}

static void	set_pwd(t_main *main)
{
	int		i;
	char	cwd[PWD_MAX_SIZE];
	char	*name_var;
	char	*var;

	i = var_defined("OLDPWD", main);
	if (i > -1)
		del_var(i, main);
	new_var("OLDPWD", main);
	i = var_defined("PWD", main);
	if (i > -1)
		del_var(i, main);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		prog_error("shell-init: error retrieving current directory", 	\
		"getcwd: cannot access parent directories", strerror(errno));
	else
	{
		name_var = ft_strdup_no_list("PWD=");
		var = ft_strjoin(name_var, cwd);
		free(name_var);
		new_var(var, main);
		free(var);
		// free(cwd);
	}
}

static void	set__(t_main *main)
{
	int	i;

	i = var_defined("_", main);
	if (i > -1)
		del_var(i, main);
	new_var("_=bash_des_freros", main);
}

void	reset_var(t_main *main)
{
	inc_shlvl(main);
	set_pwd(main);
	set__(main);
}