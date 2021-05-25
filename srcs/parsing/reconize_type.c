/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconize_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:42:57 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/25 15:01:07 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_start_cmd_actual(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int		start_cmd;
	int		i;

	start_cmd = 0;
	i = 0;
	index = main->lexer;
	while (index!= NULL)
	{
		index = index->content;
		if (tmp->type == NEW_COMMAND)
			start_cmd = i + 1;
		index = index->next;
		i++;
	}
	return (start_cmd);
}

static int	first_command(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int		start_cmd;
	int		i;

	start_cmd = find_start_cmd_actual(main);
	index = main->lexer;
	i = -1;
	while (++i < start_cmd)
		index = index->next;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == COMMAND)
			return (FALSE);
		index = index->next;
	}
	return (TRUE);
}

static int	redirection_file(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int size;
	int i;

	size = ft_lstsize(main->lexer);
	// printf("size = %d\n", size);
	index = main->lexer;
	i = -1;
	while (++i < size - 1)
		index = index->next;
	if (index == NULL || index == main->lexer)
		return (FALSE);
	tmp = index->content;
	if (tmp->type == REDIRECTION)
		return (TRUE);
	else
		return (FALSE);
}

void	reconize_type(t_lexer *lex, t_utils_lexer *utils, t_main *main)
{
	if (!ft_strncmp(";", lex->value, 2))
		lex->type = NEW_COMMAND;
	else if (!ft_strncmp("<", lex->value, 2) || !ft_strncmp(">", lex->value, 2)
		|| !ft_strncmp(">>", lex->value, 3) || !ft_strncmp("|", lex->value, 2))
		lex->type = REDIRECTION;
	else if (redirection_file(main) == TRUE)
		lex->type = FILE_NAME;
	else if (first_command(main) == TRUE)
		lex->type = COMMAND;
	else
		lex->type = ARGUMENT;
}

void	reconize_primitive_type(t_lexer *lex, t_utils_lexer *utils, t_main *m)
{
	if (!ft_strncmp(";", lex->value, 2))
		lex->type = NEW_COMMAND;
	else if (!ft_strncmp("<", lex->value, 2) || !ft_strncmp(">", lex->value, 2)
		|| !ft_strncmp(">>", lex->value, 3) || !ft_strncmp("|", lex->value, 2))
		lex->type = REDIRECTION;
	else if (utils->var_env == 1)
	{
		lex->type = VAR_ENV;
		utils->var_env = 0;
	}
	else
		lex->type = TO_DEFINE;
}