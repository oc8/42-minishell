/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:49 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/22 16:36:07 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_doule(char **src)
{
	size_t	i;

	i = 0;
	while (src[i])
		free(src[i++]);
	free(src);
}

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
		while ((dirent = readdir(dir)))
			if (!ft_strncmp(dirent->d_name, cmd, ft_strlen(cmd) + 1))
			{
				closedir(dir);
				path = ft_strdup_no_list(paths[i]);
				free_doule(paths);
				return (path);
			}
		closedir(dir);
		i++;
	}
	free_doule(paths);
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
	free_doule(var_path);
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
		printf("\033[31mbash_des_freros: %s: command not found\n\033[0m", arg[0]);
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
