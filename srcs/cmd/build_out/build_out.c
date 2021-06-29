#include "minishell.h"

static char	*cmd_path(char *cmd, t_main *main)
{
	char	**var_path;
	char	**paths;
	int		index;

	index = var_defined("PATH", main);
	if (index == -1)
		paths = 0;
	else
	{
		var_path = split_var(main->env[index], main);
		paths = ft_split(var_path[1], ':');
		ft_freedoublestr(&var_path);
	}
	return (check_path(paths, cmd, main));
}

static char	*search_cmd(char **cmd_arg, t_main *main)
{
	char	*path;
	char	*tmp;
	char	*rs_path;

	path = cmd_path(cmd_arg[0], main);
	if (!path)
	{
		cmd_error(cmd_arg[0], "command not found", 0, 127);
		return (0);
	}
	if (!path[0])
	{
		free(path);
		cmd_error(cmd_arg[0], "command not found", 0, 127);
		return (0);
	}
	rs_path = ft_strjoin(path, "/");
	free(path);
	tmp = rs_path;
	rs_path = ft_strjoin(rs_path, cmd_arg[0]);
	free(tmp);
	return (rs_path);
}

void	cmd_build_out(t_param_cmd *param, t_main *main)
{
	char	*cmd_name;
	char	**cmd_arg;

	cmd_arg = param->cmd;
	if (cmd_arg[0][0] == '/' || (cmd_arg[0][0] == '.' && cmd_arg[0][1] == '/'))
	{
		if (check_dir(cmd_arg[0]))
			return ;
		cmd_name = cmd_arg[0];
	}
	else if (cmd_arg[0][0] == '.' && !cmd_arg[0][1])
	{
		cmd_error(cmd_arg[0], \
		"filename argument required\n.: usage: . filename [arguments]", 0, 127);
		return ;
	}
	else
		cmd_name = search_cmd(cmd_arg, main);
	if (cmd_name && execve(cmd_name, cmd_arg, main->env) < 0)
		cmd_error(cmd_arg[0], strerror(errno), 0, 127);
	free(cmd_name);
}
