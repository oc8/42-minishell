/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:49 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 20:56:44 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

void	cmd_others(char **arg, t_main *main)
{
	char	*cmd;
	pid_t	pid;
	int		status;
	char	*path;

	if (!ft_strncmp(arg[0], "test", 5))
		return ;
	path = cmd_path(arg[0], main);
	// printf("'%s'\n", path);
	if (!path || !path[0])
	{
		free(path);
		cmd_error(arg[0], "command not found", 0, 127);
		return ;
	}
	cmd = ft_strjoin(path, "/");
	free(path);
	cmd = ft_strjoin(cmd, arg[0]);
	// printf("%s\n", cmd);
	pid = fork();
	if (pid == -1)
		quit_prog("error fork", main);
	else if (pid == 0)
	{
		if (execve(cmd, arg, main->env) < 0)
		// 	strerrno(errno);
			;
		exit(0);
	}
	else
		wait(&status);
	free(cmd);
}
