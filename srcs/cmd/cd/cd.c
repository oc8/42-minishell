/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:56 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/17 16:18:20 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_cd(char **arg, t_main *main)
{
	(void)main;

	if (!ft_strncmp(arg[0], ".", 2))
		return ;
	if (chdir(arg[0]) == -1)
		// quit_prog("chdir() on cd", main);
		printf("\033[31mcd error :\033[0m '%s'\n", arg[0]);
}
