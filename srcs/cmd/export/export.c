/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/24 20:58:21 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(char **arg, t_main *main)
{
	char	**var;
	size_t	*len;
	size_t	len_var;
	size_t	i;
	char	**env;

	// error if start by =
	var = ft_split(arg[0], '=');
	if (!var[1] && arg[ft_strlen(arg[0]) - 1] != '=')
		// free
		return ;
	len = &main->nbr_env;
	i = 0;
	while (main->env[i])
	{
		env = ft_split(main->env[i], '=');
		if (!ft_strncmp(env[0], var[0], ft_strlen(env[0]) + 1))
		{
			ft_lstdel_content(main->free, main->env[i]);
			free(main->env[i]);
			len_var = ft_strlen(arg[0]) + 1;
			main->env[i] = ft_calloc_lst(&main->free, len_var, sizeof(char));
			ft_strlcpy(main->env[i], arg[0], len_var);
			return ;
		}
		i++;
	}
	main->env = ft_memadd(main->env, *len, *len + 1, sizeof(char *));
	len_var = ft_strlen(arg[0]) + 1;
	main->env[*len] = ft_calloc_lst(&main->free, len_var, sizeof(char));
	ft_strlcpy(main->env[*len], arg[0], len_var);
	*len += 1;
}
