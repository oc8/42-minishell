/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:35:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/19 21:44:45 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bash_script(t_utils_lexer *utils, t_main *main)
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
	if (main->line[utils->i + 1] == '?')
	{
		update_word('$', utils, main);
		update_word('?', utils, main);
		update_word(' ', utils, main);
		update_word('A', utils, main);
		update_word(' ', utils, main);
		update_word('C', utils, main);
		update_word('O', utils, main);
		update_word('D', utils, main);
		update_word('E', utils, main);
		update_word('R', utils, main);
		update_word(' ', utils, main);
		utils->i++;
		return (TRUE);
	}
	return (FALSE);
}

static char	*get_var_name(t_utils_lexer *utils, t_main *m)
{
	size_t	i;
	size_t	j;
	char	*var;

	i = 1;
	var = NULL;
	if (bash_script(utils, m) == TRUE)
		return (NULL); 
	while (ft_isalnum(m->line[utils->i + i]) || m->line[utils->i + i] == '_')
	{
		// printf("m->line[utils->i + i] = %c\n", m->line[utils->i + i]);
		if (var != NULL)
			free(var);
		var = malloc(i + 1);
		if (var == NULL)
			quit_prog("Malloc get_var_name lexer", m);
		j = -1;
		while (++j <= i - 1)
			var[j] = m->line[utils->i + 1 + j];
		var[j] = '\0';
		i++;
	}
	// printf("TEST\n");
	if (i == 1)
		update_word('$', utils, m);
	// printf("fin get_var_name : var = |%s|\n", var);
	utils->i += i - 1;
	// printf("m->line[utils->i] = %c\n", m->line[utils->i]);
	return (var);
}

static int	var_defined(char *var, t_utils_lexer *utils, t_main *main)
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

static void	add_var(size_t indice, t_utils_lexer *utils, t_main *main)
{
	size_t	j;

	j = 0;
	while (main->env[indice][j] != '=')
		j++;
	j++;
	while (main->env[indice][j])
		update_word(main->env[indice][j++], utils, main);
}

void	check_local_var(t_utils_lexer *utils, t_main *main)
{
	int		indice_var;
	char	*var;

	indice_var = -1;
	var = get_var_name(utils, main);
	// printf("var = %s\n", var);
//			SI $ SEUL ou FINIT PAR \, IMPRIMER SEULEMENT LE $
	if (var != NULL)
		indice_var = var_defined(var, utils, main);
	// printf("indice_var = %d, main->env[indice_var] = |%s|\n", indice_var, main->env[indice_var]);
	if (indice_var != -1)
		add_var(indice_var, utils, main);
	if (var != NULL)
		free(var);
	// if (main->line[utils->i] == '\0')
	// 	return (LINE_FINISHED);
	// else
	// {
		// utils->i--;
		// return (WORD_NOT_FINISHED);
	// }
}