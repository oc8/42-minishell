/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:57:02 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/11 18:49:10 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(char **arg, t_main *main)
{
	char	cwd[PWD_MAX_SIZE];

	(void)main;
	(void)arg;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		quit_prog("getcwd() on pwd", main);
	else
		printf("%s\n", cwd);
}
