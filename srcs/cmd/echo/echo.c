/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:18:27 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 18:03:05 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(char **arg, t_main *main)
{
	int	i;
	int	flag_n;

	(void)main;
	if (!arg[0])
	{
		printf("\n");
		return ;
	}
	flag_n = 0;
	i = 0;
	if (arg[0][0] == '-')
		while (arg[0][++i] == 'n')
			;
	if (i > 1 && !arg[0][i])
	{
		flag_n = 1;
		i = 1;
	}
	else
		i = 0;
	while (arg[i])
	{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
	}
	if (!flag_n)
		printf("\n");
}
