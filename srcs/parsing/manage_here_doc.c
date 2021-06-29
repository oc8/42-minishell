#include "minishell.h"

static char	*get_var_name(int *ind, char *str, char **new, t_main *m)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 1;
	var = NULL;
	while (ft_isalnum(str[*ind + i]) || str[*ind + i] == '_')
	{
		if (var != NULL)
			free(var);
		var = malloc(i + 1);
		if (var == NULL)
			quit_prog("Malloc get_var_name lexer", m);
		j = -1;
		while (++j <= i - 1)
			var[j] = str[*ind + 1 + j];
		var[j] = '\0';
		i++;
	}
	if (i == 1 && (str[*ind + i] != '\'' || str[*ind + i] != '"'))
		update_word('$', new);
	*ind += i - 1;
	return (var);
}

static void	add_var(size_t indice, char **new, t_main *main)
{
	size_t	j;

	j = 0;
	while (main->env[indice][j] != '=')
		j++;
	j++;
	while (main->env[indice][j])
		update_word(main->env[indice][j++], new);
}

static void	normal_caracter(char c, char **new, t_utils_lexer *ut)
{
	if (c == '\\' && ut->echap == 0)
		ut->echap = 2;
	else
		update_word(c, new);
}

void	treat_here_doc_line(char **new, char *str, t_main *main)
{
	int				indice_var;
	t_utils_lexer	utils;
	char			*var;
	int				i;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && !utils.echap)
		{
			indice_var = -1;
			var = get_var_name(&i, str, new, main);
			if (var != NULL)
				indice_var = var_defined(var, main);
			if (indice_var != -1)
				add_var(indice_var, new, main);
			if (var != NULL)
				free(var);
		}
		else
			normal_caracter(str[i], new, &utils);
		if (utils.echap > 0 && str[i])
			utils.echap--;
	}
}
