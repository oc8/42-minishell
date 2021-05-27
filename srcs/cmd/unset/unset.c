/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:24 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/27 17:27:37 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_unset(char **arg, t_main *main)
{
	// char	**var;
	size_t	*len;
	size_t	i;
	int		index;

	if (!arg[0])
		return ;
	len = &main->nbr_env;
	i = 0;
	while (arg[i])
	{
		if (check_var_name(arg[i]) != 2)
			cmd_error("export", "not a valid identifier", arg[i], 1);
		// var = split_var(arg[i], main);
		// printf("%s\n", arg[i]);
		index = var_defined(arg[i], main);
		// ft_freedoublestr(&var);
		if (index > -1)
		{
			while (main->env[++index])
				main->env[index - 1] = main->env[index];
			main->env[index - 1] = 0;
			free(main->env[index]);
			main->env = ft_memadd(main->env, *len, *len - 1, sizeof(char *));
			*len -= 1;
		}
		i++;
	}
}
