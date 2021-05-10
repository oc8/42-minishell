/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:40:24 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/10 19:14:04 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reconize_type(const char *elem, t_lexer *lexer)
{
	if (!ft_strncmp("echo", elem, 5) || !ft_strncmp("cd", elem, 3)
		|| !ft_strncmp("pwd", elem, 4) || !ft_strncmp("export", elem, 7)
		|| !ft_strncmp("unset", elem, 6) || !ft_strncmp("env", elem, 4)
		|| !ft_strncmp("exit", elem, 5))
		lexer->type = COMMAND;
	else if (!ft_strncmp(";", elem, 2) || !ft_strncmp("\'", elem, 2)
		|| !ft_strncmp("\"", elem, 2) || !ft_strncmp("|", elem, 2)
		|| !ft_strncmp("$", elem, 2))
		lexer->type = OPERATOR;
	else
		lexer->type = ARGUMENT;
}

void	malloc_element(int index_line, int w_count, t_main *main)
{
	int		i;
	int		j;
	t_lexer	*lexer;
	t_list	*new;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		fail("Lexer malloc", main);
	lexer->value = malloc(w_count + 1);
	if (lexer->value == NULL)
		fail("Lexer malloc", main);
	i = index_line - w_count;
	j = 0;
	while (i < index_line)
		lexer->value[j++] = main->line[i++];
	lexer->value[j] = '\0';
	reconize_type(lexer->value, lexer);
	new = ft_lstnew(lexer);
	ft_lstadd_back(&main->lexer, new);
}

int	end_word(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '$' || c == '|' || c == '\''
		|| c == '"' || c == '\0')
		return (1);
	else
		return (0);
}

void	lexer(t_main *main)
{
	int		i;
	int		w_count;

	i = 0;
	while (main->line[i])
	{
		w_count= 0;
		while (end_word(main->line[i]) == FALSE)
		{
			i++;
			w_count++;
		}
		if (w_count > 0)
			malloc_element(i, w_count, main);
		if (main->line[i] != '\0')
			i++;
	}
}