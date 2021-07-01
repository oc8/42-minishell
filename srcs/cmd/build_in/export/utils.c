#include "minishell.h"

static void	cpy(int j, char *arg, char *str)
{
	size_t	i;

	i = j;
	if (arg[j] == '+')
		j++;
	while (arg[j])
	{
		str[i] = arg[j];
		j++;
		i++;
	}
}

void	add_var_export(int flag_add, char *arg, t_main *main)
{
	char	*str;
	size_t	j;

	if (flag_add)
	{
		j = -1;
		str = ft_calloc(ft_strlen(arg), sizeof(char));
		while (arg[++j])
		{
			if (arg[j] == '=' || arg[j] == '+')
				break ;
			str[j] = arg[j];
		}
		cpy(j, arg, str);
		new_var(str, main);
		free(str);
	}
	else
		new_var(arg, main);
}
