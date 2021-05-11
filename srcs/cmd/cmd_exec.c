/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:16:47 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/11 19:05:58 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec(int cmd, char **arg, t_main *main)
{
	int		i;

	i = 7;
	while (--i >= 0 && cmd != main->cmd_fct[i].cmd)
		;
	if (cmd == main->cmd_fct[i].cmd)
		main->cmd_fct[i].fct(arg, main);
}

void	test_cmd_exec(t_main *main)
{
	char	*tabl[4];

	if (!ft_strncmp(main->line, "exit", 5))
		cmd_exec(EXIT_CMD, 0, main);
	if (!ft_strncmp(main->line, "echo", 4))
	{
		tabl[0] = &main->line[4];
		tabl[1] = 0;
		cmd_exec(ECHO_CMD, tabl, main);
	}
	if (!ft_strncmp(main->line, "pwd", 4))
		cmd_exec(PWD_CMD, 0, main);
	if (!ft_strncmp(main->line, "cd", 2))
	{
		tabl[0] = &main->line[2];
		cmd_exec(CD_CMD, tabl, main);
	}
}
