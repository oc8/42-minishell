/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/25 21:08:40 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_main *main)
{
	char	**env;
	char	**var;
	size_t	i;

	env = main->env;
	i = 0;
	while (env[i] && i < main->nbr_env)
	{
		var = split_var(env[i], main);
		// sort
		printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		ft_freedoublestr(var);
		i++;
	}
}

int	check_var_name(char *name)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(name[i]))
		return (1);
	while (name[++i] && name[i] != '=' && name[i] != '+')
		if (!ft_isalnum(name[i]))
			return (1);
	if (name[i] == '+' && name[i + 1] != '=')
		return (1);
	if (!name[i])
		return (2);
	return (0);
}

static int	check_vars(char **arg)
{
	size_t	i;
	int		rv;

	i = 0;
	while (arg[i])
	{
		rv = check_var_name(arg[i]);
		if (rv == 1)
			return (cmd_error("export", "not a valid identifier", arg[i]));
		else if (rv == 2)
			return (1);
		i++;
	}
	return (0);
}

void	cmd_export(char **arg, t_main *main)
{
	char	**var;
	size_t	*len;
	size_t	len_var;
	size_t	i;
	char	**env;

	// error if start by '='
	if (!arg[0])
		print_env(main);
	if (check_vars(arg))
		return ;
	var = split_var(arg[0], main);
	if (!var[1] && arg[0][ft_strlen(arg[0]) - 1] != '=')
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
			ft_freedoublestr(var);
			ft_freedoublestr(env);
			return ;
		}
		ft_freedoublestr(env);
		i++;
	}
	ft_freedoublestr(var);
	main->env = ft_memadd(main->env, *len, *len + 1, sizeof(char *));
	len_var = ft_strlen(arg[0]) + 1;
	main->env[*len] = ft_calloc_lst(&main->free, len_var, sizeof(char));
	ft_strlcpy(main->env[*len], arg[0], len_var);
	*len += 1;
}
