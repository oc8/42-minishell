#include "minishell.h"

// static int	contain_char(char *var, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (var[i] && var[i] != c)
// 		i++;
// 	if (var[i] == c)
// 		return (1);
// 	return (0);
// }

void	cmd_env(t_param_cmd *param, t_main *main)
{
	size_t	i;
	int		file2;

	if (param->redir)
		file2 = redirection(param->redir, main);
	i = 0;
	while (main->env[i] && i < main->nbr_env)
	{
		if (ft_strchr(main->env[i], '='))
			printf("%s\n", main->env[i]);
		i++;
	}
	if (param->redir)
		close(file2);
}
