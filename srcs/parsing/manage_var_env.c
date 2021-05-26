/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_var_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:35:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/26 20:40:09 by odroz-ba         ###   ########lyon.fr   */
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
		indice_var = var_defined(var, main);
	// printf("indice_var = %d, main->env[indice_var] = |%s|\n", indice_var, main->env[indice_var]);
	if (indice_var != -1)
		add_var(indice_var, utils, main);
	if (var != NULL)
		free(var);
}

void	predefine_var(t_utils_lexer *utils, t_main *m)
{
	int	i;

	utils->var_env = 1;
	update_word('$', utils, m);
	utils->i++;
	while (ft_isalnum(m->line[utils->i]) || m->line[utils->i] == '_')
	{
		update_word(m->line[utils->i], utils, m);
		utils->i++;
	}
	utils->i--;
}