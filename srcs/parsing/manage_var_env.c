/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:35:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/06/01 16:48:59 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bash_script(int *ind, char *str, char **new, t_main *main)
{
	// int		i;
	// char	str;

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
	if (str[*ind] == '?')
	{
		update_word('$', new);
		update_word('?', new);
		update_word(' ', new);
		update_word('A', new);
		update_word(' ', new);
		update_word('C', new);
		update_word('O', new);
		update_word('D', new);
		update_word('E', new);
		update_word('R', new);
		update_word(' ', new);
		(*ind)++;
		return (TRUE);
	}
	return (FALSE);
}

static char	*get_var_name(int *ind, char *str, char **new, t_main *m)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 1;
	var = NULL;
	if (bash_script(ind, str, new, m) == TRUE)
		return (NULL);
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
	// printf("m->line[utils->i] = %c\n", m->line[utils->i]);
	return (var);
}

static int	var_defined(char *var, t_main *main)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (main->env[++i] != NULL)
	{
		j = 0;
		while (var[j] == main->env[i][j])
			j++;
		if (var[j] == '\0' && main->env[i][j] == '=')
			return (i);
	}
	return (-1);
}

static void	add_var(size_t indice, char **new, t_main *main)
{
	size_t	j;

	j = 0;
	while (main->env[indice][j] != '=')
		j++;
	j++;
	// printf ("add_var OK\n");
	while (main->env[indice][j])
	{
		// printf("c = %c\n", main->env[indice][j++]);
		update_word(main->env[indice][j++], new);
	}
}

void	remplace_var_value(char **new, char *str, t_main *main)
{
	int		indice_var;
	char	*var;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '$')
		{
			// printf("str[i] = %c\n", str[i]);
			update_word(str[i], new);
		}
		else
		{
			indice_var = -1;
			var = get_var_name(&i, str, new, main);
			if (var != NULL)
				indice_var = var_defined(var, main);
			// printf("indice_var = %d, main->env[indice_var] = |%s|\n", indice_var, main->env[indice_var]);
			if (indice_var != -1)
				add_var(indice_var, new, main);
			// printf("new remplace_var = %s\n", *new);
			if (var != NULL)
				free(var);
		}
	}
}

void	predefine_var(t_utils_lexer *utils, t_main *m)
{
	int	i;

		// printf("test predifine_var\n");
	if (utils->str[utils->i + 1] == '"' || utils->str[utils->i + 1] == '\'')
		return ;
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