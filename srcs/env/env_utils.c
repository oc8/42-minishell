#include "minishell.h"

void	edit_var(char *new, size_t i, t_main *main)
{
	char	**var;
	size_t	len_var;
	char	*tmp;
	t_list	*elem;

	var = split_var(main->env[i], main);
	ft_lstdel_content(&main->free, main->env[i]);
	free(main->env[i]);
	len_var = ft_strlen(new) + ft_strlen(var[0]) + 2;
	tmp = ft_strjoin(var[0], "=");
	ft_freedoublestr(&var);
	main->env[i] = ft_strjoin(tmp, new);
	free(tmp);
	elem = ft_lstnew(main->env[i]);
	if (!elem)
		quit_prog("malloc() error", main);
	ft_lstadd_front(&main->free, elem);
}

void	new_var(char *add, t_main *main)
{
	size_t	*len;
	size_t	len_var;
	t_list	*elem;

	len = &main->nbr_env;
	if (*len + 1 > main->max)
	{
		main->max *= 2;
		ft_lstdel_content(&main->free, main->env);
		main->env = (char **)realloc_double(main->max, (void ***)&main->env);
		elem = ft_lstnew(main->env);
		if (!elem)
			quit_prog("malloc() error", main);
		ft_lstadd_front(&main->free, elem);
	}
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
	*len -= 1;
}
