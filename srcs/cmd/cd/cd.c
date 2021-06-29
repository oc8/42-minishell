#include "minishell.h"

static void	save_pwd(t_main *main)
{
	char	cwd[PWD_MAX_SIZE];

	if (main->oldpwd)
	{
		free(main->oldpwd);
		main->oldpwd = 0;
	}
	if (main->pwd)
		main->oldpwd = main->pwd;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	main->pwd = ft_calloc(ft_strlen(cwd) + 1, sizeof(char));
	ft_strlcpy(main->pwd, cwd, -1);
}

static void	reset_pwd_var(t_main *main)
{
	int		i;
	int		j;
	char	**var;
	char	cwd[PWD_MAX_SIZE];

	save_pwd(main);
	i = var_defined("OLDPWD", main);
	if (i == -1)
		return ;
	j = var_defined("PWD", main);
	if (j == -1)
		return ;
	var = split_var(main->env[j], main);
	edit_var(var[1], i, main);
	ft_freedoublestr(&var);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cmd_error("cd", strerror(errno), 0, 0);
	edit_var(cwd, j, main);
	// free(cwd);
}

static int	arg_tilde(t_main *main)
{
	if (main->home_path)
	{
		if (chdir(main->home_path) == -1)
		{
			cmd_error("cd", strerror(errno), main->home_path, 1);
			return (1);
		}
	}
	return (0);
}

static int	arg_shrink(t_main *main)
{
	int		i;

	if (main->oldpwd == NULL)
		return (cmd_error("cd", "OLDPWD not set", 0, 1));
	if (chdir(main->oldpwd) == -1)
		return (cmd_error("cd", strerror(errno), main->oldpwd, 1));
	ft_putstr_fd(main->oldpwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

static int	change_location(char **arg, t_main *main)
{
	if (arg[0][0] == '-' && !arg[0][1])
	{
		if (arg_shrink(main))
			return (1);
	}
	else if (arg[0][0] == '~' && !arg[0][1])
	{
		if (arg_tilde(main))
			return (1);
	}
	else if (chdir(arg[0]) == -1)
	{
		cmd_error("cd", strerror(errno), arg[0], 1);
		return (1);
	}
	return (0);
}

void	cmd_cd(t_param_cmd *param, t_main *main)
{
	char	**arg;

	arg = param->cmd + 1;
	if (!ft_strncmp(arg[0], ".", 2))
	{
		if (getcwd(0, 0) == NULL)
		{
			prog_error("cd: error retrieving current directory",		\
			"getcwd: cannot access parent directories", strerror(errno));
			return ;
		}
	}
	else
	{
		if (change_location(arg, main))
			return ;
	}
	global.exit_status = 0;
	reset_pwd_var(main);
}
