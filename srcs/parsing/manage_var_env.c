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

static void	add_var(size_t indice, char **new, t_utils_lexer *uti, t_main *main)
{
	size_t	j;

	j = 0;
	while (main->env[indice][j] != '=')
		j++;
	j++;
	while (main->env[indice][j])
	{
		if (main->env[indice][j] == '\\' || main->env[indice][j] == '>'
			|| main->env[indice][j] == '<' || main->env[indice][j] == '|'
			|| main->env[indice][j] == ';')
			update_word('\\', new);
		update_word(main->env[indice][j++], new);
	}
}

void	normal_caracter(char c, char **new, t_utils_lexer *utils, t_main *main)
{
	if (c == '\\'
		&& ((utils->double_q == 0 && utils->sing_q == 0 && utils->echap == 0)
			|| (utils->double_q == 1 && utils->echap == 0)))
		utils->echap = 2;
	else if (c == '\'' && utils->echap == 0)
	{
		if (utils->sing_q == 0 && utils->double_q == 0)
			utils->sing_q = 1;
		else if (utils->sing_q == 1)
			utils->sing_q = 0;
	}
	else if (c == '"' && utils->echap == 0)
	{
		if (utils->double_q == 0 && utils->sing_q == 0)
			utils->double_q = 1;
		else if (utils->double_q == 1)
			utils->double_q = 0;
	}
	update_word(c, new);
}

static	void	remplace(char *str, t_utils_lexer *utils, t_main *main)
{
	int		i;
	int		indice_var;
	char	*var;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && !utils->sing_q && !utils->echap)
		{
			indice_var = -1;
			var = get_var_name(&i, str, &utils->word, main);
			if (var != NULL)
				indice_var = var_defined(var, main);
			if (indice_var != -1)
				add_var(indice_var, &utils->word, utils, main);
			if (var != NULL)
				free(var);
		}
		else
			normal_caracter(str[i], &utils->word, utils, main);
		if (utils->echap > 0 && str[i])
			utils->echap--;
	}
}

char	**remplace_var_value(char *str, t_main *main)
{
	char			**split;
	t_utils_lexer	utils;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	split = NULL;
	remplace(str, &utils, main);
	split = split_var_parsing(utils.word);
	free(utils.word);
	return (split);
}
