/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:49 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/25 21:11:29 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *check_path(char **paths, char *cmd)
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
		while ((dirent = readdir(dir)))
			if (!ft_strncmp(dirent->d_name, cmd, ft_strlen(cmd) + 1))
			{
				closedir(dir);
				path = ft_strdup_no_list(paths[i]);
				ft_freedoublestr(paths);
				return (path);
			}
		closedir(dir);
		i++;
	}
	ft_freedoublestr(paths);
	return (ft_strdup_no_list(""));
}

static char	*cmd_path(char *cmd, t_main *main)
{
	char	**var_path;
	char	**paths;
	size_t	i;

	i = 0;
	while (main->env[i])
	{
		var_path = ft_split(main->env[i], '=');
		if (!ft_strncmp("PATH", var_path[0], 5))
			break ;
		i++;
	}
	if (ft_strncmp("PATH", var_path[0], 5))
		paths = 0;
	else
		paths = ft_split(var_path[1], ':');
	ft_freedoublestr(var_path);
	return (check_path(paths, cmd));
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
		cmd_error(arg[0], "command not found", 0);
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
		printf("%d\n", execve(cmd, arg, main->env));
		exit(0);
	}
	else
		wait(&status);
	free(cmd);
}
