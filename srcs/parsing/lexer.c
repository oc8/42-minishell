/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:40:24 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/19 22:03:36 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_element(t_utils_lexer *utils, t_main *main)
{
	t_lexer	*lexer;
	t_list	*new;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		quit_prog("Lexer creation malloc", main);
	lexer->value = ft_strdup_no_list(utils->word);
	if (lexer->value == NULL)
		quit_prog("Lexer value malloc", main);
	free(utils->word);
	utils->word = NULL;
	reconize_type(lexer->value, lexer, main);
	new = ft_lstnew(lexer);
	ft_lstadd_back(&main->lexer, new);
}

void	update_word(char c, t_utils_lexer *utils, t_main *main)
{
	char	*new;
	int		len;
	int		i;

	if (utils->word != NULL)
	{
		new = malloc(ft_strlen(utils->word) + 2);
		len = ft_strlen(utils->word);
	}
	else
	{
		new = malloc(2);
		len = 0;
	}
	i = -1;
	while (++i < len)
		new[i] = utils->word[i];
	new[i] = c;
	i++;
	new[i] = '\0';
	if (utils->word != NULL)
		free(utils->word);
	utils->word = new;
}

int	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\0')
		return (LINE_FINISHED);
	else if (c == '\\')
	{
		if ((utils->double_q == 0 && utils->sing_q == 0 && utils->echap == 0)
			|| (utils->double_q == 1 && utils->echap == 0))
			utils->echap = 2;
		else
			update_word(c, utils, main);
		return (WORD_NOT_FINISHED);
	}
	else if (c == '\'')
	{
		if (utils->double_q == 1 || (utils->double_q == 0 && utils->echap == 1))
			update_word(c, utils, main);
		else if (utils->sing_q == 0 && utils->double_q == 0)
			utils->sing_q = 1;
		else if (utils->sing_q == 1)
			utils->sing_q = 0;
		return (WORD_NOT_FINISHED);
	}
	else if (c == '"')
	{
		if (utils->sing_q == 1 || (utils->double_q == 1 && utils->echap == 1))
			update_word(c, utils, main);
		else if (utils->double_q == 0 && utils->sing_q == 0)
			utils->double_q = 1;
		else if (utils->double_q == 1)
			utils->double_q = 0;
		return (WORD_NOT_FINISHED);
	}
	else if (c == '$')
	{
		if (utils->sing_q == 1 || (utils->double_q == 1 && utils->echap == 1))
			update_word(c, utils, main);
		else
			check_local_var(utils, main);
		return (WORD_NOT_FINISHED);
	}
	else if (c == '>' || c == '<' || c == '|' || c == ' ' || c == ';')
	{
		if (utils->sing_q == 1 || utils->double_q == 1)
		{
			if (utils->double_q == 1 && utils->echap == 1)
				update_word('\\', utils, main);
			update_word(c, utils, main);
			return (WORD_NOT_FINISHED);
		}
		else if (c == ' ')
			return (SPACE);
		else
			return (WORD_FINISHED);
	}
	else
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', utils, main);
		update_word(c, utils, main);
		return (WORD_NOT_FINISHED);
	}
}

void	lexer(t_main *main)
{
	t_utils_lexer	utils;
	t_caracter_lex	res;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	// main->nb_elem_lex = 0;
	res = WORD_NOT_FINISHED;
	while (res != LINE_FINISHED) // && res != NEW_COMMAND)
	{
		res = check_caracter_lex(main->line[utils.i], &utils, main);
		if (utils.echap > 0 && res != LINE_FINISHED)
			utils.echap--;
		// printf("char = %c, res = %d\n", main->line[utils.i], res);
		// if (res == WORD_FINISHED || res == LINE_FINISHED)
		if (res != WORD_NOT_FINISHED)
		{
			// if (utils.w_count > 0)
			if (utils.word)
				// malloc_element(utils.i, utils.w_count, main);
				malloc_element(&utils, main);
			if (res == WORD_FINISHED)
			{
				// utils.w_count = 1;
				// malloc_element(utils.i + 1, utils.w_count, main);
				update_word(main->line[utils.i], &utils, main);
				if (utils.word[0] == '>' && main->line[utils.i + 1] == '>')
				{
					update_word('>', &utils, main);
					utils.i++;
				}
				malloc_element(&utils, main);
			}
		}
		if (res != LINE_FINISHED)
			utils.i++;
	}
	if (utils.word)
		// malloc_element(utils.i, utils.w_count, main);
		malloc_element(&utils, main);
	if (utils.echap || utils.double_q || utils.sing_q)
	{
		printf("Error : Multiline is not accepted\n");
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		// free(main->line);
		// main->line = NULL;
		// return;
	}
}
