/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 20:17:37 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 21:36:32 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_new_command(int i, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	
	if (i == 0)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	index = main->lexer;
	while (--i > 0)
		index = index->next;
	tmp = index->content;
	if (tmp->type == NEW_COMMAND)
	{
		printf("bash: syntax error near unexpected token `%s'\n", tmp->value);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	return (1);
}

static int	verify_redirection(int i, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	
	if (i == ft_lstsize(main->lexer) - 1)
	{
		printf("bash: syntax error near unexpected token `nexline'\n");
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	index = main->lexer;
	while (--i >= 0)
		index = index->next;
	index = index->next;
	tmp = index->content;
	if (tmp->type != TO_DEFINE && tmp->type != FILE_NAME && tmp->type != VAR_ENV)
	{
		printf("bash: syntax error near unexpected token `%s'\n", tmp->value);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		return (-1);
	}
	return (1);
}

void	verify_syntax(t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int		i;
	
	if (utils->echap || utils->double_q || utils->sing_q)
	{
		printf("Error : Multiline is not accepted\n");
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
	}
	i = 0;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if ((tmp->type == REDIR_INPUT || tmp->type == REDIR_OUTPUT
			|| tmp->type == APPEND_REDIR_OUTPUT)
			&& verify_redirection(i, utils, main) == -1)
				return ;
		else if (tmp->type == NEW_COMMAND
			&& verify_new_command(i, utils, main) == -1)
				return ;
		index = index->next;
		i++;
	}
}
