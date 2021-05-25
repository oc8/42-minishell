/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconize_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:42:57 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/29 16:58:31 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	find_start_cmd_actual(t_main *main)
// {
// 	t_list	*index;
// 	t_lexer	*tmp;
// 	int		start_cmd;
// 	int		i;

// 	start_cmd = 0;
// 	i = 0;
// 	index = main->lexer;
// 	while (index!= NULL)
// 	{
// 		tmp = index->content;
// 		if (tmp->type == NEW_COMMAND)
// 			start_cmd = i + 1;
// 		index = index->next;
// 		i++;
// 	}
// 	return (start_cmd);
// }

static int	first_command(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	// int		start_cmd;
	// int		i;

	// start_cmd = find_start_cmd_actual(main);
	index = main->lexer;
	// i = -1;
	// while (++i < start_cmd)
	// 	index = index->next;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == COMMAND)
			return (FALSE);
		index = index->next;
	}
	return (TRUE);
}

static int	redirection_file(int i, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	// int size;

	if (i == 0)
		return (FALSE);

	// size = ft_lstsize(main->lexer);
	// printf("size = %d\n", size);

	index = main->lexer;
	while (--i > 0)
		index = index->next;
	tmp = index->content;
	if (tmp->type == REDIR_OUTPUT || tmp->type == REDIR_INPUT
		|| tmp->type == APPEND_REDIR_OUTPUT)
		return (TRUE);
	else
		return (FALSE);
}

// static int	is_not_arg()

void	define_text_types(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int		i;
	
	i = 0;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == TO_DEFINE)
		{
			if (redirection_file(i, main) == TRUE)
				tmp->type = FILE_NAME;
			else if (first_command(main) == TRUE)
				tmp->type = COMMAND;
			else
				tmp->type = ARGUMENT;
		}
		index = index->next;
		i++;
	}
}

void	reconize_primitive_type(t_lexer *lex, t_utils_lexer *utils, t_main *m)
{
	(void)m;
	if (utils->var_env == 1)
	{
		lex->type = VAR_ENV;
		utils->var_env = 0;
	}
	else
		lex->type = TO_DEFINE;
}