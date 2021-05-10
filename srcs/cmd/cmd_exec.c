/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:16:47 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/10 18:36:56 by odroz-ba         ###   ########lyon.fr   */
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
		tabl[0] = ft_strdup(&main->free, "-n");
		tabl[1] = ft_strdup(&main->free, "test1 ");
		tabl[2] = ft_strdup(&main->free, "test2");
		tabl[3] = 0;
		cmd_echo(tabl);
	}
}
