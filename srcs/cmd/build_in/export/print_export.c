#include "minishell.h"

static size_t	max_alphabetical(char **src)
{
	size_t	i;
	size_t	i_min;

	i = 0;
	i_min = 0;
	while (src[i])
	{
		if (ft_strncmp(src[i], src[i_min], -1) > 0)
			i_min = i;
		i++;
	}
	return (i_min);
}

static void	print_export_var(char **env, int i_min, t_main *main)
{
	char	**var;

	var = split_var(env[i_min], main);
	if (!(var[0][0] == '_' && !var[0][1]))
	{
		if (var[1])
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		else
			printf("declare -x %s\n", var[0]);
	}
	ft_freedoublestr(&var);
}

void	print_export(t_main *main)
{
	char	**env;
	int		*sort;
	size_t	i;
	size_t	j;
	size_t	i_min;

	env = main->env;
	i = 0;
	sort = ft_calloc(main->nbr_env, sizeof(int));
	while (env[i] && i < main->nbr_env)
	{
		j = -1;
		i_min = max_alphabetical(env);
		while (env[++j] && j < main->nbr_env)
			if (!sort[j] && ft_strncmp(env[j], env[i_min], -1) < 0)
				i_min = j;
		if (sort[i_min])
			break ;
		sort[i_min] = 1;
		print_export_var(env, i_min, main);
		i++;
	}
	free(sort);
}
