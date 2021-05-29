#include "minishell.h"

// static int	bash_script(t_utils_lexer *utils, t_main *main)
// {
// 	// int		i;
// 	// char	str;

// 	// printf("m->line[utils->i] = %c\n", main->line[utils->i]);
// 	// if (ft_isdigit(main->line[utils->i + 1]) == TRUE)
// 	// {
// 	// 	printf("Error : This terminal only use bash script \"$?\"\n");
// 	// 	utils->i++;
// 	// 	// while (ft_isdigit(main->line[utils->i]))
// 	// 	// 	utils->i++;
// 	// 	// utils->i--;
// 	// 	return (TRUE);
// 	// }
// 	if (main->line[utils->i + 1] == '?')
// 	{
// 		update_word('$', utils);
// 		update_word('?', utils, main);
// 		update_word(' ', utils, main);
// 		update_word('A', utils, main);
// 		update_word(' ', utils, main);
// 		update_word('C', utils, main);
// 		update_word('O', utils, main);
// 		update_word('D', utils, main);
// 		update_word('E', utils, main);
// 		update_word('R', utils, main);
// 		update_word(' ', utils, main);
// 		utils->i++;
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

// static char	*get_var_name(int ind, char *str, t_main *m)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*var;

// 	i = 1;
// 	var = NULL;
// 	if (bash_script(utils, m) == TRUE)
// 		return (NULL); 
// 	while (ft_isalnum(utils->str[utils->i + i]) || utils->str[utils->i + i] == '_')
// 	{
// 		// printf("m->line[utils->i + i] = %c\n", m->line[utils->i + i]);
// 		if (var != NULL)
// 			free(var);
// 		var = malloc(i + 1);
// 		if (var == NULL)
// 			quit_prog("Malloc get_var_name lexer", m);
// 		j = -1;
// 		while (++j <= i - 1)
// 			var[j] = m->line[utils->i + 1 + j];
// 		var[j] = '\0';
// 		i++;
// 	}
// 	// printf("TEST\n");
// 	if (i == 1 && (utils->str[utils->i + i] != '\'' || utils->str[utils->i + i] != '"'))
// 		update_word('$', &utils->word);
// 	// printf("fin get_var_name : var = |%s|\n", var);
// 	utils->i += i - 1;
// 	// printf("m->line[utils->i] = %c\n", m->line[utils->i]);
// 	return (var);
// }

// static void	add_var(size_t indice, t_utils_lexer *utils, t_main *main)
// {
// 	size_t	j;

// 	j = 0;
// 	while (main->env[indice][j] != '=')
// 		j++;
// 	j++;
// 	while (main->env[indice][j])
// 		update_word(main->env[indice][j++], &utils->word);
// }

// void	remplace_var_value(char **new, char *str, t_main *main)
// {
// 	int		indice_var;
// 	char	*var;
// 	int		i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] != '$')
// 			update_word(str[i], new);
// 		else
// 		{
// 			indice_var = -1;
// 			var = get_var_name(i, main);
// 			if (var != NULL)
// 				indice_var = var_defined(var, main);
// 			// printf("indice_var = %d, main->env[indice_var] = |%s|\n", indice_var, main->env[indice_var]);
// 			if (indice_var != -1)
// 				add_var(indice_var, utils, main);
// 			if (var != NULL)
// 				free(var);
// 		}
// 	}
// }

void	predefine_var(t_utils_lexer *utils, t_main *m)
{
	int	i;

	utils->var_env = 1;
	update_word('$', &utils->word);
	utils->i++;
	while (utils->str[utils->i] != ' ' && utils->str[utils->i])
	{
		update_word(m->line[utils->i], &utils->word);
		utils->i++;
	}
	utils->i--;
}