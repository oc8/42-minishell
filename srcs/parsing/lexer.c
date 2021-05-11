/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:40:24 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/11 19:14:04 by tdayde           ###   ########lyon.fr   */
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
	else if (!ft_strncmp(";", elem, 2) || !ft_strncmp(">", elem, 2)
		|| !ft_strncmp("<", elem, 2) || !ft_strncmp("|", elem, 2))
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
		quit_prog("Lexer malloc", main);
	lexer->value = malloc(w_count + 1);
	if (lexer->value == NULL)
		quit_prog("Lexer malloc", main);
	i = index_line - w_count;
	j = 0;
	while (i < index_line)
		lexer->value[j++] = main->line[i++];
	lexer->value[j] = '\0';
	reconize_type(lexer->value, lexer);
	new = ft_lstnew(lexer);
	ft_lstadd_back(&main->lexer, new);
}

// int	end_word(char c)
// {
// 	if (c == '\0')
// 		return (LINE_FINISHED);
// 	else if (c == ' ' || c == '>' || c == '<' || c == '$' || c == '|' || c == '\''
// 		|| c == '"' || c == ';')
// 		return (WORD_FINISHED);
// 	else
// 		return (WORD_NOT_FINISHED);
// }

int	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\0')
		return (LINE_FINISHED);
	else if (c == '\\')
	{
		if ((utils->double_q == 0 && utils->sing_q == 0)
			|| (utils->double_q == 1 && (main->line[utils->i + 1] == '"'
				|| main->line[utils->i + 1] == '$'
				|| main->line[utils->i + 1] == '\\')))
			utils->echap = 1;
		else
			utils->w_count++;
		return (WORD_NOT_FINISHED);
	}
	else if (c == '\'')
	{
		if (utils->double_q == 1 || (utils->double_q == 0 && utils->echap == 1))
			utils->w_count++;
		else if (utils->sing_q == 0 && utils->double_q == 0)
			utils->sing_q = 1;
		else if (utils->sing_q == 1)
			utils->sing_q = 0;
		return (WORD_NOT_FINISHED);
	}
	else if (c == '"')
	{
		if (utils->sing_q == 1 || (utils->double_q == 1 && utils->echap == 1))
			utils->w_count++;
		else if (utils->double_q == 0 && utils->sing_q == 0)
			utils->double_q = 1;
		else if (utils->double_q == 1)
			utils->double_q = 0;
		return (WORD_NOT_FINISHED);
	}
	// else if (c == '$')
	// {
	// 	if (utils->sing_q == 1 || (utils->double_q == 1 && utils->echap == 1))
	// 	{
	// 		utils->w_count++;
	// 		return (WORD_NOT_FINISHED);
	// 	}
	// 	else if (utils->double_q == 0 && utils->sing_q == 0)
	// 	{
	// 		utils->double_q = 1;
	// 		return (WORD_FINISHED);
	// 	}
	// 	else if (utils->double_q == 1)
	// 	{
	// 		utils->double_q = 0;
	// 		return (WORD_FINISHED);
	// 	}
	// }
	else if (c == ' ')
	{
		if (utils->sing_q == 1 || utils->double_q == 1)
		{
			utils->w_count++;
			return (WORD_NOT_FINISHED);
		}
		else
			return (WORD_FINISHED);
	}
	else if (c == '>' || c == '<' || c == ';')
	{
		if (utils->sing_q == 1 || utils->double_q == 1)
		{
			utils->w_count++;
			return (WORD_NOT_FINISHED);
		}
		else
			return (WORD_FINISHED);
	}
	else
	{
		utils->w_count++;
		return (WORD_NOT_FINISHED);
	}
}

void	lexer(t_main *main)
{
	t_utils_lexer	utils;
	int				res;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	while (main->line[utils.i])
	{
		res = check_caracter_lex(main->line[utils.i], &utils, main);
		// printf("char = %c, res = %d\n", main->line[utils.i], res);
		if (res == WORD_FINISHED || res == LINE_FINISHED)
		{
			// printf("w_count = %d\n", utils.w_count);
			if (utils.w_count > 0)
				malloc_element(utils.i, utils.w_count, main);
			if (res == WORD_FINISHED && main->line[utils.i] != ' ')
			{
				utils.w_count = 1;
				malloc_element(utils.i + 1, utils.w_count, main);
			}
				utils.w_count = 0;
		}
		if (res != LINE_FINISHED)
			utils.i++;
	}
	if (utils.w_count > 0)
		malloc_element(utils.i, utils.w_count, main);

	// i = 0;
	// while (main->line[i])
	// {
	// 	w_count= 0;
	// 	while (end_word(main->line[i]) == WORD_NOT_FINISHED)
	// 	{
	// 		i++;
	// 		w_count++;
	// 	}
	// 	if (w_count > 0)
	// 		malloc_element(i, w_count, main);
	// 	if (end_word(main->line[i]) == WORD_FINISHED)
	// 	{
	// 		i++;
	// 		w_count++;
	// 	}
	// 	if (w_count > 0)
	// 		malloc_element(i, w_count, main);
	// 	if (main->line[i] != '\0')
	// 		i++;
	// }
}