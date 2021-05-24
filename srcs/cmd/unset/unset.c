/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:24 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/24 15:47:28 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	cmd_unset(char **arg, t_main *main)
{
	(void)arg;
	(void)main;
	char	**var;
	char	**env;
	size_t	i;

	var = ft_split(arg[0], '=');
	i = 0;
	while (main->env[i])
	{
		env = ft_split(main->env[i], '=');
		if (env[0] == var[0])
		{
			while (main->env[i])
			{
				main->env[i - 1] = main->env[i];
				i++;
			}
			main->env[i - 1] = 0;
			main->env = ft_memadd(main->env, 10, 10 - 1, sizeof(char *));
			break ;
		}
		i++;
	}
}
