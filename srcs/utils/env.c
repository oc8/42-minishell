#include "minishell.h"

void	add_to_var(char *add, size_t i, t_main *main)
{
	char	**env;
	size_t	len_var;

	env = split_var(main->env[i], main);
	ft_lstdel_content(main->free, main->env[i]);
	free(main->env[i]);
	len_var = ft_strlen(add) + 1;
	main->env[i] = ft_calloc_lst(&main->free, len_var, sizeof(char));
	ft_strlcpy(main->env[i], add, len_var);
	// ft_freedoublestr(&env);
}

void	new_var(char *add, t_main *main)
{
	size_t	*len;
	size_t	len_var;

	len = &main->nbr_env;
	main->env = ft_memadd(main->env, *len, *len + 1, sizeof(char *));
	len_var = ft_strlen(add) + 1;
	main->env[*len] = ft_calloc_lst(&main->free, len_var, sizeof(char));
	ft_strlcpy(main->env[*len], add, len_var);
	*len += 1;
}
