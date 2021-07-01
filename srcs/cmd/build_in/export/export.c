#include "minishell.h"

static void	add_to_var(char *add, int index, t_main *main)
{
	char	*tmp;
	t_list	*elem;

	tmp = main->env[index];
	ft_lstdel_content(&main->free, main->env[index]);
	main->env[index] = ft_strjoin(main->env[index], add);
	elem = ft_lstnew(main->env[index]);
	if (!elem)
		quit_prog("malloc() error", main);
	ft_lstadd_front(&main->free, elem);
	free(tmp);
}

static int	is_add(char *name_var)
{
	if (name_var[ft_strlen(name_var) - 1] == '+')
	{
		name_var[ft_strlen(name_var) - 1] = 0;
		return (1);
	}
	return (0);
}

static void	export_var(char **arg, int i, t_main *main)
{
	int		flag_add;
	char	**var;
	int		index;

	if (check_var_name(arg[i]) == 1)
		cmd_error("export", "not a valid identifier", arg[i], 1);
	var = split_var(arg[i], main);
	flag_add = is_add(var[0]);
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
		add_var_export(flag_add, arg[i], main);
	ft_freedoublestr(&var);
}

void	cmd_export(t_param_cmd *param, t_main *main)
{
	size_t	i;
	char	**arg;

	arg = param->cmd + 1;
	if (!arg[0])
	{
		print_export(main);
		return ;
	}
	i = 0;
	while (arg[i])
	{
		export_var(arg, i, main);
		i++;
	}
}
