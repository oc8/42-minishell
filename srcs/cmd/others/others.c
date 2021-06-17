#include "minishell.h"

static char *check_path(char **paths, char *cmd, t_main *main)
{
	size_t			i;
	DIR				*dir;
	struct dirent	*dirent;
	char			*path;

	i = 0;
	if (!paths)
		return (ft_strdup_no_list(""));
	while (paths[i])
	{
		dir = opendir(paths[i]);
		if (!dir)
			quit_prog("opendir(): error", main);
		while ((dirent = readdir(dir)))
			if (!ft_strncmp(dirent->d_name, cmd, ft_strlen(cmd) + 1))
			{
				closedir(dir);
				path = ft_strdup_no_list(paths[i]);
				ft_freedoublestr(&paths);
				// free(path); // ? leaks
				return (path);
			}
		closedir(dir);
		i++;
	}
	ft_freedoublestr(&paths);
	return (ft_strdup_no_list(""));
}

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

void	cmd_others(t_param_cmd *param, t_main *main)
{
	char	*cmd;
	char	*path;
	char	**arg;

	arg = param->cmd;
	if (!ft_strncmp(arg[0], "test", 4))
		return ;
	if (arg[0][0] == '/' || (arg[0][0] == '.' && arg[0][1] == '/'))
		cmd = arg[0];
	else
	{
		path = cmd_path(arg[0], main);
		if (!path || !path[0])
		{
			free(path);
			main->exit_status = cmd_error(arg[0], "command not found", 0, 127);
			return ;
		}
		cmd = ft_strjoin(path, "/");
		free(path);
		cmd = ft_strjoin(cmd, arg[0]);
	}
	arg[0] = cmd;
	if (execve(cmd, arg, main->env) < 0)
		main->exit_status = cmd_error(arg[0], strerror(errno), 0, 127);
	free(cmd); // free
}
