#include "minishell.h"

static void	bash_script(t_utils_lexer *utils, t_main *main)
{
	char	*exit_status;
	int		i;
	
	exit_status = ft_itoa(main->exit_status);
	i = -1;
	while (exit_status[++i])
		update_word(exit_status[i], &utils->word);
	free(exit_status);
	utils->i++;


	// printf("m->line[utils->i] = %c\n", main->line[utils->i]);
	// if (ft_isdigit(main->line[utils->i + 1]) == TRUE)
	// {
	// 	printf("Error : This terminal only use bash script \"$?\"\n");
	// 	utils->i++;
	// 	// while (ft_isdigit(main->line[utils->i]))
	// 	// 	utils->i++;
	// 	// utils->i--;
	// 	return (TRUE);
	// }
	// if (utils->str[utils->i + 1] == '?')
	// {
		// update_word('$', &utils->word);
		// update_word('?', &utils->word);
		// update_word(' ', &utils->word);
		// update_word('A', &utils->word);
		// update_word(' ', &utils->word);
		// update_word('C', &utils->word);
		// update_word('O', &utils->word);
		// update_word('D', &utils->word);
		// update_word('E', &utils->word);
		// update_word('R', &utils->word);
		// utils->i++;
		// return (TRUE);
	// }
	// return (FALSE);
}

static char	*get_var_name(int *ind, char *str, char **new, t_main *m)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 1;
	var = NULL;
	// if (bash_script(ind, str, new, m) == TRUE)
	// 	return (NULL);
	while (ft_isalnum(str[*ind + i]) || str[*ind + i] == '_')
	{
		// printf("m->line[utils->i + i] = %c\n", m->line[utils->i + i]);
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
	// printf("TEST\n");
	if (i == 1 && (str[*ind + i] != '\'' || str[*ind + i] != '"'))
		update_word('$', new);
	// printf("fin get_var_name : var = |%s|\n", var);
	*ind += i - 1;
	// printf("fin get_var_name i = %d\n", *ind);
	// printf("m->line[utils->i] = %c\n", m->line[utils->i]);
	return (var);
}

static void	add_var(size_t indice, char **new, t_utils_lexer *uti, t_main *main)
{
	size_t	j;

	j = 0;
	while (main->env[indice][j] != '=')
		j++;
	j++;
	// printf("main->env[indice] = |%s|\n", main->env[indice]);
	if (uti->double_q == 0)
		update_word('"', new);
	while (main->env[indice][j])
	{
		// printf("c = |%c|\n", main->env[indice][j]);
		update_word(main->env[indice][j++], new);
	}
	if (uti->double_q == 0)
		update_word('"', new);
}

void	remplace_var_value(char **new, char *str, t_main *main)
{
	int				indice_var;
	t_utils_lexer	utils;
	char			*var;
	int				i;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	i = -1;
	// printf("str_with_var = %s, new = %s\n", str, *new);
	while (str[++i])
	{
		// printf("%c", str[i]);
		if (str[i] == '$' && !utils.sing_q && !utils.echap)
		{
			indice_var = -1;
			var = get_var_name(&i, str, new, main);
			if (var != NULL)
				indice_var = var_defined(var, main);
			// printf("indice_var = %d, main->env[indice_var] = |%s|\n", indice_var, main->env[indice_var]);
			if (indice_var != -1)
				add_var(indice_var, new, &utils, main);
			// printf("new remplace_var = %s\n", *new);
			if (var != NULL)
				free(var);
			// printf("fin get_var_name i = %d\n", i);
		}
		else
		{
			// printf("%c", str[i]);
			if (str[i] == '\\'
				&& ((utils.double_q == 0 && utils.sing_q == 0 && utils.echap == 0)
				|| (utils.double_q == 1 && utils.echap == 0)))
				utils.echap = 2;
			else if (str[i] == '\'' && utils.echap == 0)
			{
				if (utils.sing_q == 0 && utils.double_q == 0)
					utils.sing_q = 1;
				else if (utils.sing_q == 1)
					utils.sing_q = 0;
			}
			else if (str[i] == '"' && utils.echap == 0)
			{
				if (utils.double_q == 0 && utils.sing_q == 0)
					utils.double_q = 1;
				else if (utils.double_q == 1)
					utils.double_q = 0;
			}
			update_word(str[i], new);
		}
		if (utils.echap > 0 && str[i])
			utils.echap--;
	}
		// printf("str_with_var = %s, new = %s\n", str, *new);
}

void	predefine_var(t_utils_lexer *utils, t_main *m)
{
	// int	i;

	// if (utils->str[utils->i + 1])
	// 	utils->var_env = 1;
	// if (utils->word)
	// 	i = utils->i - ft_strlen(utils->word);
	// else 
	// 	i = utils->i;
	// while (utils->str[i])


	if (utils->str[utils->i + 1] == '"' || utils->str[utils->i + 1] == '\'')
		return ;
	if (utils->str[utils->i + 1] == '?')
	{
		printf("test\n");
		bash_script(utils, m);
		return ;
	}
	if (!ft_isalpha(utils->str[utils->i + 1]) && utils->str[utils->i + 1] != '_'
		&& utils->str[utils->i + 1])
	{
		utils->i++;
		return ;
	}
	update_word('$', &utils->word);
	if (utils->str[utils->i + 1])
		utils->var_env = 1;

	// utils->i++;
	// while (utils->str[utils->i] != ' ' && utils->str[utils->i])
	// {
	// 	update_word(m->line[utils->i], &utils->word);
	// 	utils->i++;
	// }
	// utils->i--;
}