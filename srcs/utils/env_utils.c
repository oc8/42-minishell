#include "minishell.h"

void	edit_var(char *new, size_t i, t_main *main)
{
	char	**var;
	size_t	len_var;
	char	*tmp;

	var = split_var(main->env[i], main);
	ft_lstdel_content(&main->free, main->env[i]);
	free(main->env[i]);
	len_var = ft_strlen(new) + ft_strlen(var[0]) + 2;
	// main->env[i] = ft_calloc_lst(&main->free, len_var, sizeof(char));
	tmp = ft_strjoin(var[0], "=");
	ft_freedoublestr(&var);
	main->env[i] = ft_strjoin(tmp, new);
	free(tmp);
	ft_lstadd_front(&main->free, ft_lstnew(main->env[i]));
	// ft_strlcpy(main->env[i], new, len_var);
}

void	new_var(char *add, t_main *main)
{
	size_t	*len;
	size_t	len_var;

	len = &main->nbr_env;
	if (*len + 1 > main->max) // >= ?
	{
		ft_lstdel_content(&main->free, &main->env);
		main->max *= 2;
		main->env = (char **)realloc_double(main->max, (void ***)&main->env);
		ft_lstadd_front(&main->free, ft_lstnew(main->env));
	}
	// main->env = ft_memadd(main->env, *len, *len + 1, sizeof(char *));
	// ft_lstadd_back(&main->free, ft_lstnew(&main->env));
	len_var = ft_strlen(add) + 1;
	main->env[*len] = ft_calloc_lst(&main->free, len_var, sizeof(char));
	ft_strlcpy(main->env[*len], add, len_var);
	*len += 1;
}

void	del_var(int index, t_main *main)
{
	size_t	*len;

	len = &main->nbr_env;
	while (main->env[++index])
		main->env[index - 1] = main->env[index];
	main->env[index - 1] = 0;
	ft_lstdel_content(&main->free, &main->env[index]);
	free(main->env[index]);
	// main->env = ft_memadd(main->env, *len, *len - 1, sizeof(char *));
	*len -= 1;
}
