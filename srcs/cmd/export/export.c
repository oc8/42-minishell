#include "minishell.h"

static void	print_env(t_main *main)
{
	char	**env;
	char	**var;
	size_t	*sort;
	size_t	i;
	size_t	j;
	size_t	i_min;
	int		diff;
	int		min;

	env = main->env;
	i = 0;
	i_min = 0;
	sort = ft_calloc(main->nbr_env, sizeof(size_t));
	while (env[i] && i < main->nbr_env)
	{
		min = 255;
		j = 0;
		while (env[j] && j < main->nbr_env)
		{
			diff = ft_strncmp(env[j], env[i_min], -1);
			if (!sort[j] && diff < min)
			{
				i_min = j;
				min = diff;
			}
			j++;
		}
		sort[i_min] = 1;
		var = split_var(env[i_min], main);
		if (var[1])
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		else
			printf("declare -x %s\n", var[0]);
		ft_freedoublestr(&var);
		i++;
	}
	free(sort);
}

static void	add_to_var(char *add, int index, t_main *main)
{
	char	*tmp;

	// tmp = ft_calloc(ft_strlen(main->env[index]), sizeof(char));
	// ft_strlcpy(tmp, main->env[index], ft_strlen(main->env[index]));
	// free(main->env[index]);
	tmp = main->env[index];
	main->env[index] = ft_strjoin(main->env[index], add);
	free(tmp);
}

void	cmd_export(t_param_cmd *param, t_main *main)
{
	char	**var;
	size_t	i;
	int		index;
	int		flag_add;
	char	**arg;

	arg = param->cmd + 1;
	if (!arg[0])
	{
		print_env(main);
		return ;
	}
	i = 0;
	while (arg[i])
	{
		if (check_var_name(arg[i]) == 1)
			cmd_error("export", "not a valid identifier", arg[i], 1);
		var = split_var(arg[i], main);
		flag_add = 0;
		if (var[0][ft_strlen(var[0]) - 1] == '+')
		{
			var[0][ft_strlen(var[0]) - 1] = 0;
			flag_add = 1;
		}
		index = var_defined(var[0], main);
		if (!ft_strchr(arg[i], '=') && index > -1)
		{
			ft_freedoublestr(&var);
			return ;
		}
		if (index > -1 && !flag_add)
			edit_var(var[1], index, main);
		else if (index > -1)
			add_to_var(var[1], index, main);
		else
			new_var(arg[i], main);
		ft_freedoublestr(&var);
		i++;
	}
}
