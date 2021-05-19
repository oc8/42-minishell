/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconize_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:42:57 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/19 21:59:43 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_start_cmd_actual(t_main *main)
{
	t_list	*tmp;
	t_lexer	*tmp2;
	int		start_cmd;
	int		i;

	start_cmd = 0;
	i = 0;
	tmp = main->lexer;
	while (tmp != NULL)
	{
		tmp2 = tmp->content;
		if (tmp2->type == NEW_COMMAND)
			start_cmd = i + 1;
		tmp = tmp->next;
		i++;
	}
	return (start_cmd);
}

static int	first_command(t_main *main)
{
	t_list	*tmp;
	t_lexer	*tmp2;
	int		start_cmd;
	int		i;

	start_cmd = find_start_cmd_actual(main);
	tmp = main->lexer;
	i = -1;
	while (++i < start_cmd)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		tmp2 = tmp->content;
		if (tmp2->type == COMMAND)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

static int	redirection_file(t_main *main)
{
	t_list	*tmp;
	t_lexer	*tmp2;
	int size;
	int i;

	size = ft_lstsize(main->lexer);
	printf("size = %d\n", size);
	tmp = main->lexer;
	i = -1;
	while (++i < size - 1)
		tmp = tmp->next;
	if (tmp == NULL || tmp == main->lexer)
		return (FALSE);
		
	tmp2 = tmp->content;
	if (tmp2->type == REDIRECTION)
		return (TRUE);
	else
		return (FALSE);
}

void	reconize_type(const char *elem, t_lexer *lexer, t_main *main)
{
	if (!ft_strncmp(";", elem, 2))
		lexer->type = NEW_COMMAND;
	else if (!ft_strncmp("<", elem, 2) || !ft_strncmp(">", elem, 2)
		|| !ft_strncmp(">>", elem, 3) || !ft_strncmp("|", elem, 2))
		lexer->type = REDIRECTION;
	else if (redirection_file(main) == TRUE)
		lexer->type = FILE_NAME;
	else if (first_command(main) == TRUE)
		lexer->type = COMMAND;
	else
		lexer->type = ARGUMENT;
}