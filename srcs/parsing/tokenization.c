/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:40:24 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/31 22:06:33 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_list(t_list **new, t_utils_lexer *utils, t_main *main)
{
	t_list	*index;
	t_list	*next;
	t_lexer	*tmp;
	int		i;
	
	// tmp = (*new)->content;
	// printf("cmd = %s, utils->i_lst = %d\n", tmp->value, utils->i_lst);
	if (utils->i_lst == 0)
		ft_lstadd_back(&main->lexer, *new);
	else if (utils->i_lst == 1)
	{
		ft_lstadd_front(&main->lexer, *new);
		utils->i_lst++;
	}
	else
	{
		i = utils->i_lst;
		index = main->lexer;
		while (--i > 1)
			index = index->next;
		next = index->next;
		index->next = *new;
		(*new)->next = next;
		utils->i_lst++;
	}
}

void	malloc_element(t_type_lex type, t_utils_lexer *utils, t_main *main)
{
	t_lexer	*lexer;
	t_list	*index;
	t_list	*new;
	int		i;

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
	add_to_list(&new, utils, main);

	// if (utils->i_lst == 0)
	// 	ft_lstadd_back(&main->lexer, new);
	// else
	// {
	// 	i = utils->i_lst;
	// 	index = main->lexer;
	// 	while (--i > 0)
	// 	{
	// 		index = index->next;
	// 	}

	// }

}

void	update_word(char c, char **str)
{
	char	*new;
	int		len;
	int		i;

	if (*str != NULL)
	{
		new = malloc(ft_strlen(*str) + 2);
		len = ft_strlen(*str);
	}
	else
	{
		new = malloc(2);
		len = 0;
	}
	i = -1;
	while (++i < len)
		new[i] = (*str)[i];
	new[i] = c;
	i++;
	new[i] = '\0';
	if (*str != NULL)
		free(*str);
	*str = new;
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
	// if (indice != 0)
	// 	utils.double_q = 1;
	// res = WORD_NOT_FINISHED;
	while (str[utils.i])
	{
		// res = check_caracter_lex(str[utils.i], &utils, main);
		check_caracter_lex(str[utils.i], &utils, main);
		if (utils.echap > 0 && str[utils.i])
			utils.echap--;
		// printf("char = %c\n", str[utils.i]);
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
	// printf("fin tokenisation\n");
	free(utils.str);
}
