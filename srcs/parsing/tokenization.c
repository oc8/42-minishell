/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:40:24 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 19:18:04 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_element(t_type_lex type, t_utils_lexer *utils, t_main *main)
{
	t_lexer	*lexer;
	t_list	*new;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		quit_prog("Lexer malloc creation", main);
	lexer->value = ft_strdup_no_list(utils->word);
	if (lexer->value == NULL)
		quit_prog("Lexer value malloc", main);
	if (type == -1)
		reconize_primitive_type(lexer, utils, main);
	else
		lexer->type = type;
	utils->word = NULL;
	free(utils->word);
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

// void	add_special_token(char *str, t_utils_lexer *utils, t_main *main)
// {
// 	int			i;
// 	long long	fd;
	
// 	if (str[utils->i] == '>' || str[utils->i] == '<')
// 	{
// 		i = utils->i;
// 		fd = 0;
// 		while (--i >= 0 && ft_isdigit(str[i]))
// 			fd = fd * 10 + str[i] - '0';
// 		if (i > 0)
// 		{
// 			if (str[i] == ';' || str[i] == '|' || str[i] == ' '
// 				|| str[i] == '\'' || str[i] == '"' || str[i] == ' ')
// 		}
			
// 	}
// }

void	tokenization(char *str, int indice, t_main *main)
{
	t_utils_lexer	utils;
	t_caracter_lex	res;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	utils.i_lst = indice;
	utils.str = ft_strdup_no_list(str);
	if (utils.str == NULL)
		quit_prog("strdup of str to analize in tokenisation", main);
	if (indice != 0)
		utils.double_q = 1;
	// res = WORD_NOT_FINISHED;
	while (str[utils.i])
	{
		// res = check_caracter_lex(str[utils.i], &utils, main);
		check_caracter_lex(str[utils.i], &utils, main);
		if (utils.echap > 0 && str[utils.i])
			utils.echap--;
		// printf("char = %c, res = %d\n", str[utils.i], res);
		// if (res == WORD_FINISHED || res == LINE_FINISHED)
		// if (res != WORD_NOT_FINISHED)
		// {
			// if (utils.word) // A VOIR NOMBRE DU FD DE REDIRECTION POUR MALLOC!!!
			// 	malloc_element(&utils, main);
			// if (res == WORD_FINISHED)
			// {
			// 	update_word(str[utils.i], &utils, main);
			// 	if (utils.word[0] == '>' && str[utils.i + 1] == '>')
			// 	{
			// 		update_word('>', &utils, main);
			// 		utils.i++;
			// 	}
			// 	malloc_element(&utils, main);
			// }
		// }
		if (str[utils.i])
			utils.i++;
	}
	if (utils.word)
		malloc_element(-1, &utils, main);
	verify_syntax(&utils, main);
	free(utils.str);
}
