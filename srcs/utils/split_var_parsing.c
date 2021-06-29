#include "minishell.h"

static void	normal_caracter(char c, char **new, t_utils_lexer *utils)
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
	if (new)
		update_word(c, new);
}

static int	count_words(char *str)
{
	int				i;
	t_utils_lexer	utils;
	int				n_word;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	n_word = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\' || str[i] == '\'' || str[i] == '"')
			normal_caracter(str[i], NULL, &utils);
		else if (str[i] == ' ' && str[i + 1] != ' '
			&& !utils.echap && !utils.sing_q && !utils.double_q)
			n_word++;
		if (utils.echap > 0 && str[i])
			utils.echap--;
	}
	return (n_word);
}

char	**split_var_parsing(char *str)
{
	char			**split;
	int				ind;
	t_utils_lexer	utils;
	int				i;

	ft_bzero(&utils, sizeof(utils));
	split = ft_calloc(count_words(str) + 1, sizeof(char *));
	ind = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i + 1] != ' ' && i != 1
			&& !utils.echap && !utils.sing_q && !utils.double_q)
			ind++;
		normal_caracter(str[i], &split[ind], &utils);
		if (utils.echap > 0 && str[i])
			utils.echap--;
	}
	split[ind + 1] = NULL;
	return (split);
}
