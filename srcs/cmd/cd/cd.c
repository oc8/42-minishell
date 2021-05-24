/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:56 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/24 14:17:54 by odroz-ba         ###   ########lyon.fr   */
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
		printf("\033[31mbash_des_freros: cd: %s: No such file or directory\n", arg[0]);
}
