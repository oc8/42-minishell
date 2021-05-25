/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:24 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/25 21:08:52 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_vars(char **arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (check_var_name(arg[i]) != 2)
			return (cmd_error("export", "not a valid identifier", arg[i]));
		i++;
	}
	return (0);
}

void	cmd_unset(char **arg, t_main *main)
{
	char	**var;
	char	**env;
	size_t	*len;
	size_t	i;

	if (!arg[0] || check_vars(arg))
		return ;
	len = &main->nbr_env;
	var = ft_split(arg[0], '=');
	i = 0;
	while (main->env[i])
	{
		env = ft_split(main->env[i], '=');
		if (!ft_strncmp(env[0], var[0], ft_strlen(var[0]) + 1))
		{
			while (main->env[++i])
				main->env[i - 1] = main->env[i];
			main->env[i - 1] = 0;
			free(main->env[i]);
			main->env = ft_memadd(main->env, *len, *len - 1, sizeof(char *));
			*len -= 1;
			break ;
		}
		i++;
		ft_freedoublestr(env);
	}
	ft_freedoublestr(var);
}
