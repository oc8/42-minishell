/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:56:40 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/26 21:10:15 by odroz-ba         ###   ########lyon.fr   */
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
		if (var[1])
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		else
			printf("declare -x %s\n", var[0]);
		ft_freedoublestr(&var);
		i++;
	}
}

int	check_var_name(char *name)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (1);
	while (name[++i] && name[i] != '=' && name[i] != '+')
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
	if (name[i] == '+' && name[i + 1] != '=')
		return (1);
	if (!name[i])
		return (2);
	return (0);
}

void	cmd_export(char **arg, t_main *main)
{
	char	**var;
	size_t	i;
	size_t	index;

	if (!arg[0])
		print_env(main);
	i = 0;
	while (arg[i])
	{
		if (check_var_name(arg[i]) == 1)
			cmd_error("export", "not a valid identifier", arg[i], 1);
		var = split_var(arg[i], main);
		index = var_defined(var[0], main);
		// ft_freedoublestr(&var);
		if (index > -1)
			add_to_var(arg[i], index, main);
		else
			new_var(arg[i], main);
		i++;
	}
}
