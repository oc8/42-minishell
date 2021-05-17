/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:49 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/17 18:22:08 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_others(char **arg, t_main *main)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	cmd = ft_strjoin("/bin/", arg[0]);
	pid = fork();
	if (pid == -1) 
		quit_prog("error fork", main);
	else if (pid == 0)
		printf("%d\n", execve(cmd, arg, main->env));
	else
		wait(&status);
	// printf("pid = %d\n", getpid());
}
