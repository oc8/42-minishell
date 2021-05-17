/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:40:24 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/17 19:34:35 by tdayde           ###   ########lyon.fr   */
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
	else if (!ft_strncmp("<", elem, 2) || !ft_strncmp(">", elem, 2)
		|| !ft_strncmp(">>", elem, 3) || !ft_strncmp("|", elem, 2))
		lexer->type = OPERATOR;
	else
		lexer->type = ARGUMENT;
}

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
	reconize_type(lexer->value, lexer);
	new = ft_lstnew(lexer);
	ft_lstadd_back(&main->lexer, new);
	
	// int		i;
	// int		j;
	// lexer = malloc(sizeof(t_lexer));
	// if (!lexer)
	// 	quit_prog("Lexer malloc", main);
	// lexer->value = malloc(w_count + 1);
	// if (lexer->value == NULL)
	// 	quit_prog("Lexer malloc", main);
	// i = index_line - w_count;
	// j = 0;
	// while (i < index_line)
	// 	lexer->value[j++] = main->line[i++];
	// lexer->value[j] = '\0';
	// reconize_type(lexer->value, lexer);
	// new = ft_lstnew(lexer);
	// ft_lstadd_back(&main->lexer, new);
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

void	update_line(t_caracter_lex res, t_utils_lexer *utils, t_main *main)
{
	char	*new_line;
	size_t	i;
	size_t	j;
	
	if (res == NEW_COMMAND)
	{
		new_line = malloc(sizeof(char) * ft_strlen(main->line) - utils->i + 1);
		i = utils->i;
		j = 0;
		while (main->line[i])
			new_line[j++] = main->line[i++];
		new_line[j] = '\0';
		free(main->line);
		main->line = new_line;
		// printf("NEW COMMAND because ; ! \n");
	}
	else if (res == LINE_FINISHED)
	{
		free(main->line);
		main->line = NULL;
	}
}

int	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\0')
		return (LINE_FINISHED);
	else if (c == '\\')
	{
		if ((utils->double_q == 0 && utils->sing_q == 0)
			|| (utils->double_q == 1 && utils->echap == 0))
			utils->echap = 2;
		else
			// utils->w_count++;
			update_word(c, utils, main);
		return (WORD_NOT_FINISHED);
	}
	else if (c == '\'')
	{
		if (utils->double_q == 1 || (utils->double_q == 0 && utils->echap == 1))
			// utils->w_count++;
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
			// utils->w_count++;
			update_word(c, utils, main);
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
	else if (c == '>' || c == '<' || c == '|' || c == ' ' || c == ';')
	{
		if (utils->sing_q == 1 || utils->double_q == 1)
		{
			// utils->w_count++;
			update_word(c, utils, main);
			return (WORD_NOT_FINISHED);
		}
		else if (c == ' ')
			return (SPACE);
		else if (c == ';')
			return (NEW_COMMAND);
		else
			return (WORD_FINISHED);
	}
	else
	{
		// utils->w_count++;
		update_word(c, utils, main);
		return (WORD_NOT_FINISHED);
	}
}

void	lexer(t_main *main)
{
	t_utils_lexer	utils;
	t_caracter_lex	res;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	res = WORD_NOT_FINISHED;
	while (res != LINE_FINISHED && res != NEW_COMMAND)
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
		free(main->line);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
		main->line = NULL;
		return;
	}
	update_line(res, &utils, main);

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