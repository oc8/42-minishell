#include "minishell.h"

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
	free(utils->word);
	utils->word = NULL;
	if (lexer->value == NULL)
		quit_prog("Lexer value malloc", main);
	if (type == -1)
		reconize_primitive_type(lexer, utils, main);
	else
		lexer->type = type;
	new = ft_lstnew(lexer);
	ft_lstadd_back(&main->lexer, new);
	utils->start_word = -1;
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

void	tokenization(char *str, int indice, t_main *main)
{
	t_utils_lexer	utils;
	t_caracter_lex	res;

	ft_bzero(&utils, sizeof(t_utils_lexer));
	utils.i_lst = indice;
	utils.str = ft_strdup_no_list(str);
	if (utils.str == NULL)
		quit_prog("strdup of str to analize in tokenisation", main);
	while (str[utils.i])
	{
		if (utils.start_word == -1 && str[utils.i] != ' ')
			utils.start_word = utils.i;
		check_caracter_lex(str[utils.i], &utils, main);
		if (utils.echap > 0 && str[utils.i])
			utils.echap--;
		if (str[utils.i])
			utils.i++;
	}
	if (utils.word)
		malloc_element(-1, &utils, main);
	verify_syntax(&utils, main);
	free(utils.str);
}
