/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:16:47 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/11 16:34:35 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec(t_main *main)
{
	char	*tabl[4];

	if (!ft_strncmp(main->line, "exit", 5))
		cmd_exit(main);
	if (!ft_strncmp(main->line, "echo", 4))
	{
		tabl[0] = &main->line[5];
		tabl[1] = 0;
		cmd_echo(tabl);
	}
	if (!ft_strncmp(main->line, "pwd", 4))
		cmd_pwd(main);
	if (!ft_strncmp(main->line, "cd", 2))
	{
		tabl[0] = &main->line[3];
		cmd_cd(main, tabl);
	}
}
