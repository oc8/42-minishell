#include "minishell.h"

static void	reset_pwd_var(t_main *main)
{
	int		i;
	int		j;
	char	**var;
	char	cwd[PWD_MAX_SIZE];

	if (main->oldpwd)
	{
		ft_lstdel_content(main->free, main->oldpwd);
		free(main->oldpwd);
		main->oldpwd = 0;
	}
	if (main->pwd)
		main->oldpwd = main->pwd;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cmd_error("cd", strerror(errno), 0, 0);
	main->pwd = ft_calloc_lst(&main->free, ft_strlen(cwd) + 1, sizeof(char));
	ft_strlcpy(main->pwd, cwd, -1);
	i = var_defined("OLDPWD", main);
	if (i == -1)
		return ;
	j = var_defined("PWD", main);
	if (j == -1)
		return ;
	var = split_var(main->env[j], main);
	edit_var(var[1], i, main);
	ft_freedoublestr(&var);
	edit_var(cwd, j, main);
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
	char	**var;
	int		i;

	i = var_defined("OLDPWD", main);
	if (i == -1)
		return (cmd_error("cd", "OLDPWD not set", 0, 1));
	var = split_var(main->env[i], main);
	if (!var[1])
		return (cmd_error("cd", "OLDPWD not set", 0, 1));
	if (chdir(var[1]) == -1)
		return (cmd_error("cd", strerror(errno), var[1], 1));
	ft_putstr_fd(var[1], 1);
	ft_putstr_fd("\n", 1);
	ft_freedoublestr(&var);
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
	else if (arg[0][0] == '-' && !arg[0][1])
	{
		if (arg_shrink(main))
			return ;
	}
	else if (arg[0][0] == '~' && !arg[0][1])
	{
		if (arg_tilde(main))
			return ;
	}
	else
	{
		if (chdir(arg[0]) == -1)
		{
			cmd_error("cd", strerror(errno), arg[0], 1);
			return ;
		}
	}
	global.exit_status = 0;
	reset_pwd_var(main);
}
