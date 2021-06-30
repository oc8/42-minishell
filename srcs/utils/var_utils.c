#include "minishell.h"

static char	*content_var(size_t equal, char *var, size_t i, t_main *main)
{
	char	*name;
	char	*content;

	content = ft_calloc(ft_strlen(&var[i + 1]) + 1, sizeof(char));
	if (!content)
		quit_prog("malloc error", main);
	i = 0;
	while (var[++equal])
		content[i++] = var[equal];
	content[i] = 0;
	return (content);
}

static char	*name_var(size_t equal, char *var, size_t *i, t_main *main)
{
	char	*name;

	name = ft_calloc(equal + 1, sizeof(char));
	if (!name)
		quit_prog("malloc error", main);
	*i = 0;
	while (*i < equal)
	{
		name[*i] = var[*i];
		*i += 1;
	}
	name[*i] = 0;
	return (name);
}

char	**split_var(char *var, t_main *main)
{
	char	**rs;
	size_t	equal;
	size_t	i;

	rs = ft_calloc(3, sizeof(char *));
	if (!rs)
		quit_prog("malloc error", main);
	equal = 0;
	while (var[equal] && var[equal] != '=')
		equal++;
	if (var[equal] != '=')
	{
		rs[0] = ft_strdup_no_list(var);
		rs[1] = 0;
		return (rs);
	}
	rs[0] = name_var(equal, var, &i, main);
	rs[1] = content_var(equal, var, i, main);
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
