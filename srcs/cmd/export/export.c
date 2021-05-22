/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/22 13:14:07 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(char **arg, t_main *main)
{
	// char	**var;

	// var = ft_split(arg[0], '=');
	main->env = ft_memadd(main->env, 10, 10 + 1, sizeof(char *));
	main->env[10 - 1] = arg[0];
}
