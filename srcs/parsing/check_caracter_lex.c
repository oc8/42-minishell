/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caracter_lex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:36:30 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/26 20:09:18 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_caracter_lex	backslash(char c, t_utils_lexer *utils, t_main *main)
{
	if ((utils->double_q == 0 && utils->sing_q == 0 && utils->echap == 0)
		|| (utils->double_q == 1 && utils->echap == 0))
		utils->echap = 2;
	else
		update_word(c, utils, main);
	return (WORD_NOT_FINISHED);
}

static t_caracter_lex	quotes(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\'')
	{
		if (utils->double_q == 1 || utils->echap == 1)
			update_word(c, utils, main);
		else if (utils->sing_q == 0 && utils->double_q == 0)
			utils->sing_q = 1;
		else if (utils->sing_q == 1)
			utils->sing_q = 0;
	}
	else if (c == '"')
	{
		if (utils->sing_q == 1 || utils->echap == 1)
			update_word(c, utils, main);
		else if (utils->double_q == 0 && utils->sing_q == 0)
			utils->double_q = 1;
		else if (utils->double_q == 1)
			utils->double_q = 0;
	}
	return (WORD_NOT_FINISHED);
}

static t_caracter_lex	carac_spec(char c, t_utils_lexer *utils, t_main *main)
{
	if (utils->sing_q == 1 || (utils->double_q == 1)
		|| utils->echap == 1)
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', utils, main);
		update_word(c, utils, main);
		// printf("echap = %d, s_sing_q = %d, double_q = %d, word = %s\n", utils->echap, utils->sing_q, utils->double_q, utils->word);
		return (WORD_NOT_FINISHED);
	}
	else if (c == ' ')
		return (SPACE);
	else
		return (WORD_FINISHED);
}

int	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\0')
		return (LINE_FINISHED);
	else if (c == '\\')
		return (backslash(c, utils, main));
	else if (c == '\'' || c == '"')
		return (quotes(c, utils, main));
	else if (c == '$')
	{
		if (utils->sing_q == 1 || utils->echap == 1)
			update_word(c, utils, main);
		else
		{
			// if (utils->i_lst == 0)
				predefine_var(utils, main);
			// else
			// 	check_local_var(utils, main);
		}
		return (WORD_NOT_FINISHED);
	}
	else if (c == '>' || c == '<' || c == '|' || c == ' ' || c == ';')
		return (carac_spec(c, utils, main));
	else
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', utils, main);
		update_word(c, utils, main);
		return (WORD_NOT_FINISHED);
	}
}
