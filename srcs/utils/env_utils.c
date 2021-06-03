#include "minishell.h"

void	edit_var(char *new, size_t i, t_main *main)
{
	char	**env;
	size_t	len_var;
	char	*tmp;

	env = split_var(main->env[i], main);
	ft_lstdel_content(main->free, main->env[i]);
	free(main->env[i]);
	len_var = ft_strlen(new) + ft_strlen(env[0]) + 2;
	main->env[i] = ft_calloc_lst(&main->free, len_var, sizeof(char));
	tmp = ft_strjoin(env[0], "=");
	ft_freedoublestr(&env);
	main->env[i] = ft_strjoin(tmp, new);
	free(tmp);
	// ft_strlcpy(main->env[i], new, len_var);
}

void	new_var(char *add, t_main *main)
{
	size_t	*len;
	size_t	len_var;

	len = &main->nbr_env;
	// ft_lstdel_content(main->free, &main->env);
	main->env = ft_memadd(main->env, *len, *len + 1, sizeof(char *));
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
	ft_lstdel_content(main->free, &main->env[index]);
	free(main->env[index]);
	main->env = ft_memadd(main->env, *len, *len - 1, sizeof(char *));
	*len -= 1;
}
