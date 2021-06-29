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
			if (!ft_strncmp(dirent->d_name, cmd, ft_strlen(cmd) + 1) && dirent->d_type != DT_DIR)
			{
				// printf("type : '%d'\n", dirent->d_type);
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


// static char	**cmd_path(char *cmd, t_main *main)
// {
// 	char	**var_path;
// 	char	**paths;
// 	int		index;

// 	index = var_defined("PATH", main);
// 	if (index == -1)
// 		paths = 0;
// 	else
// 	{
// 		var_path = split_var(main->env[index], main);
// 		paths = ft_split(var_path[1], ':');
// 		ft_freedoublestr(&var_path);
// 	}
// 	return (paths);
// }

// void	cmd_others(t_param_cmd *param, t_main *main)
// {
// 	char	*path;
// 	char	**paths;
// 	char	**cmd_arg;
// 	size_t	i;

// 	cmd_arg = param->cmd;
// 	if (cmd_arg[0][0] == '/' || (cmd_arg[0][0] == '.' && cmd_arg[0][1] == '/'))
// 	{
// 		path = cmd_arg[0];
// 		if (execve(path, cmd_arg, main->env) < 0)
// 			cmd_error(cmd_arg[0], strerror(errno), 0, 127);
// 		free(path); // free
// 	}
// 	else if (cmd_arg[0][0] == '.' && !cmd_arg[0][1])
// 	{
// 		cmd_error(cmd_arg[0], "filename argument required\n.: usage: . filename [arguments]", 0, 2);
// 		return ;
// 	}
// 	else
// 	{
// 		paths = cmd_path(cmd_arg[0], main);
// 		if (!paths || !paths[0])
// 		{
// 			ft_freedoublestr(&paths);
// 			cmd_error(cmd_arg[0], "command not found", 0, 127);
// 			return ;
// 		}
// 		i = 0;
// 		while (paths[i])
// 		{
// 			path = ft_strjoin(paths[i], "/");
// 			path = ft_strjoin(path, cmd_arg[0]);
// 			// cmd_arg[0] = path;
// 			if (execve(path, cmd_arg, main->env) < 0)
// 				// cmd_error(cmd_arg[0], strerror(errno), 0, 127);
// 				;
// 			free(path);
// 			i++;
// 		}
// 	}
// 	cmd_error(cmd_arg[0], "command not found", 0, 127);
// 	// cmd_arg[0] = path;
// 	// if (execve(path, cmd_arg, main->env) < 0)
// 	// 	cmd_error(cmd_arg[0], strerror(errno), 0, 127);
// 	ft_freedoublestr(&paths); // free
// }



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

static int	check_dir(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(path);
	if (!dir)
		return (0);
	while ((dirent = readdir(dir)))
		if (dirent->d_type == DT_DIR)
		{
			closedir(dir);
			cmd_error(path, "is a directory", 0, 126);
			return (1);
		}
	closedir(dir);
	return (0);
}

void	cmd_others(t_param_cmd *param, t_main *main)
{
	char	*cmd_name;
	char	*path;
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
		cmd_error(cmd_arg[0], "filename argument required\n.: usage: . filename [arguments]", 0, 127);
		return ;
	}
	else
	{
		path = cmd_path(cmd_arg[0], main);
		if (!path || !path[0])
		{
			free(path);
			cmd_error(cmd_arg[0], "command not found", 0, 127);
			return ;
		}
		cmd_name = ft_strjoin(path, "/");
		free(path);
		cmd_name = ft_strjoin(cmd_name, cmd_arg[0]);
	}
	cmd_arg[0] = cmd_name;
	if (execve(cmd_arg[0], cmd_arg, main->env) < 0)
		cmd_error(cmd_arg[0], strerror(errno), 0, 127);
	// free(cmd_name); // free
}
