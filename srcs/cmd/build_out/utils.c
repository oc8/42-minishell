#include "minishell.h"

int	check_dir(char *path)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(path);
	if (!dir)
		return (0);
	while (42)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (dirent->d_type == DT_DIR)
		{
			closedir(dir);
			cmd_error(path, "is a directory", 0, 126);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static char	*search_in_dir(DIR *dir, char **paths, int i, char *cmd)
{
	struct dirent	*dirent;
	char			*path;

	while (42)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (!ft_strncmp(dirent->d_name, cmd, ft_strlen(cmd) + 1) \
			&& dirent->d_type != DT_DIR)
		{
			closedir(dir);
			path = ft_strdup_no_list(paths[i]);
			ft_freedoublestr(&paths);
			return (path);
		}
	}
	return (NULL);
}

char	*check_path(char **paths, char *cmd, t_main *main)
{
	size_t			i;
	DIR				*dir;
	char			*path;

	i = 0;
	if (!paths)
		return (ft_strdup_no_list(""));
	while (paths[i])
	{
		dir = opendir(paths[i]);
		if (!dir)
			quit_prog("opendir(): error", main);
		path = search_in_dir(dir, paths, i, cmd);
		if (path)
			return (path);
		closedir(dir);
		i++;
	}
	ft_freedoublestr(&paths);
	return (ft_strdup_no_list(""));
}
