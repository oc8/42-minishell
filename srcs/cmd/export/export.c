/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/24 16:06:50 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(char **arg, t_main *main)
{
	// char	**var;
	size_t	len;

	// var = ft_split(arg[0], '=');
	len = main->nbr_env + 1;
	main->env = ft_memadd(main->env, len, len + 1, sizeof(char *));
	main->env[len - 1] = arg[0];
}
