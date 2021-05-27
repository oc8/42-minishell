/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caracter_lex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:36:30 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 16:03:29 by tdayde           ###   ########lyon.fr   */
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

static t_caracter_lex	reconize_carac_spec(t_utils_lexer *utils)
{
	int	i;

	i = -1;
	while (utils->word[++i])
	{
		if (utils->word[i] == ';')
			return (NEW_COMMAND);
		else if (utils->word[i] == '|')
			return (PIPE);
		else if (utils->word[i] == '<')
			return (REDIRECTION_INPUT);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '\0')
			return (REDIRECTION_OUTPUT);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '>')
			return (APPEND_REDIRECTION_OUTPUT);
	}
	return (-1);
}

static t_caracter_lex	carac_spec(char c, t_utils_lexer *utils, t_main *main)
{
	if (utils->sing_q == 1 || (utils->double_q == 1) || utils->echap == 1)
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
	{
		if (utils->word)
			malloc_element(&utils, main);
		update_word(utils->str[utils->i], &utils, main);
		if (utils->word[utils->i] == '>' && utils->str[utils->i + 1] == '>')
		{
			update_word('>', &utils, main);
			utils->i++;
		}
		malloc_element(&utils, main);
	}
}

static t_caracter_lex	is_fd_redir(char c, t_utils_lexer *utils, t_main *main)
{
	int i;
	
	if (utils->sing_q == 1 || utils->double_q == 1 || utils->echap == 1)
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', utils, main);
		update_word(c, utils, main);
		// printf("echap = %d, s_sing_q = %d, double_q = %d, word = %s\n", utils->echap, utils->sing_q, utils->double_q, utils->word);
		return (WORD_NOT_FINISHED);
	}
	else
	{
		i = utils->i;
		while (ft_isdigit(utils->str[i]))
			i++;
		if (utils->str[i] == '>' || utils->str[i] == '<')
		{
			utils->i--;
			while (++utils->i <= i)
				update_word(utils->str[utils->i], utils, main);
			if (utils->str[i + 1] == '>')
			{
				update_word(c, utils, main);
				utils->i++;
			}
			printf("TEST\n");
			return (WORD_FINISHED);
		}
		else
			update_word(c, utils, main);
		return (WORD_NOT_FINISHED);
	}
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
	else if (ft_isdigit(c) == TRUE)
		return (is_fd_redir(c, utils, main));
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
