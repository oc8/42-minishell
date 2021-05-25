/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caracter_lex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:36:30 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/29 16:55:52 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	backslash(char c, t_utils_lexer *utils, t_main *main)
{
	(void)main;
	if ((utils->double_q == 0 && utils->sing_q == 0 && utils->echap == 0)
		|| (utils->double_q == 1 && utils->echap == 0))
		utils->echap = 2;
	else
		update_word(c, &utils->word);
	// return (WORD_NOT_FINISHED);
}

static void	quotes(char c, t_utils_lexer *utils, t_main *main)
{
	(void)main;
	if (c == '\'')
	{
		if (utils->double_q == 1 || utils->echap == 1)
			update_word(c, &utils->word);
		else if (utils->sing_q == 0 && utils->double_q == 0)
			utils->sing_q = 1;
		else if (utils->sing_q == 1)
			utils->sing_q = 0;
	}
	else if (c == '"')
	{
		if (utils->sing_q == 1 || utils->echap == 1)
			update_word(c, &utils->word);
		else if (utils->double_q == 0 && utils->sing_q == 0)
			utils->double_q = 1;
		else if (utils->double_q == 1)
			utils->double_q = 0;
	}
	// return (WORD_NOT_FINISHED);
}

static t_type_lex	reconize_carac_spec(t_utils_lexer *utils)
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
			return (REDIR_INPUT);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '\0')
			return (REDIR_OUTPUT);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '>')
			return (APPEND_REDIR_OUTPUT);
	}
	return (-1);
}

static void	carac_spec(char c, t_utils_lexer *utils, t_main *main)
{
	if (utils->sing_q == 1 || (utils->double_q == 1) || utils->echap == 1)
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', &utils->word);
		update_word(c, &utils->word);
		// printf("echap = %d, s_sing_q = %d, double_q = %d, word = %s\n", utils->echap, utils->sing_q, utils->double_q, utils->word);
		// return (WORD_NOT_FINISHED);
	}
	else if (c == ' ')
	{
		if (utils->word)
			malloc_element(-1, utils, main);
	}
	else
	{
		if (utils->word)
			malloc_element(-1, utils, main);
		update_word(utils->str[utils->i], &utils->word);
		if (utils->str[utils->i] == '>' && utils->str[utils->i + 1] == '>')
		{
			update_word('>', &utils->word);
			utils->i++;
		}
		malloc_element(reconize_carac_spec(utils), utils, main);
	}
}

static void	is_fd_redir(char c, t_utils_lexer *utils, t_main *main)
{
	int i;
	
	if (utils->sing_q == 1 || utils->double_q == 1 || utils->echap == 1)
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', &utils->word);
		update_word(c, &utils->word);
		// printf("echap = %d, s_sing_q = %d, double_q = %d, word = %s\n", utils->echap, utils->sing_q, utils->double_q, utils->word);
		// return (WORD_NOT_FINISHED);
	}
	else
	{
		i = utils->i;
		while (ft_isdigit(utils->str[i]))
			i++;
		if (utils->str[i] == '>' || utils->str[i] == '<')
		{
			while (utils->i < i)
			// {
			// 	printf("utils->i = %d, i = %d\n", utils->i, i);
				update_word(utils->str[utils->i++], &utils->word);
			// }
			update_word(utils->str[utils->i], &utils->word);
			if (utils->str[utils->i + 1] == '>')
				update_word(utils->str[utils->i++], &utils->word);
			malloc_element(reconize_carac_spec(utils), utils, main);
			// return (WORD_FINISHED);
		}
		else
			update_word(c, &utils->word);
		// return (WORD_NOT_FINISHED);
	}
}

void	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\0')
		return ;
		// return (LINE_FINISHED);
	else if (c == '\\')
		return (backslash(c, utils, main));
	else if (c == '\'' || c == '"')
		return (quotes(c, utils, main));
	else if (c == '$')
	{
		if (utils->sing_q == 1 || utils->echap == 1)
			update_word(c, &utils->word);
		else
		{
			// if (utils->i_lst == 0)
				predefine_var(utils, main);
			// else
			// 	check_caracter_var(utils, main);
		}
	}
	else if (ft_isdigit(c) == TRUE)
		return (is_fd_redir(c, utils, main));
	else if (c == '>' || c == '<' || c == '|' || c == ' ' || c == ';')
		return (carac_spec(c, utils, main));
	else
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', &utils->word);
		update_word(c, &utils->word);
		// printf("c = %c\n", c);
		// return (WORD_NOT_FINISHED);
	}
}
