#include "minishell.h"

char	**split_var(char *var, t_main *main)
{
	char	**rs;
	size_t	i;
	size_t	equal;

	// if (!var)
	// 	return (0);
	rs = ft_calloc(3, sizeof(char *));
	if (!rs)
		quit_prog("malloc error", main);
	equal = 0;
	while (var[equal] && var[equal] != '=')
		equal++;
	if (var[equal] != '=') // ?
	{
		rs[0] = ft_strdup_no_list(var);
		rs[1] = 0;
		return (rs);
	}
	rs[0] = ft_calloc(equal + 1, sizeof(char));
	if (!rs)
		quit_prog("malloc error", main);
	i = 0;
	while (i < equal)
	{
		rs[0][i] = var[i];
		i++;
	}
	rs[0][i] = 0;
	rs[1] = ft_calloc(ft_strlen(&var[i + 1]) + 1, sizeof(char));
	if (!rs)
		quit_prog("malloc error", main);
	i = 0;
	while (var[++equal])
		rs[1][i++] = var[equal];
	rs[1][i] = 0;
	rs[2] = 0;
	return (rs);
}

int	var_defined(char *var, t_main *main)
{
	size_t	i;
	size_t	j;

	if (main->env == NULL)
		return (-1);
	i = 0;
	while (main->env[i] != NULL)
	{
		j = 0;
		while (var[j] && var[j] == main->env[i][j])
			j++;
		if (var[j] == '\0' && (main->env[i][j] == '=' || !main->env[i][j]))
			return (i);
		i++;
	}
	return (-1);
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
