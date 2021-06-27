#include "minishell.h"

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
		else if (utils->word[i] == '<' && utils->word[i + 1] == '\0')
			return (REDIR_IN);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '\0')
			return (REDIR_OUT);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '>')
			return (APP_REDIR_OUT);
		else if (utils->word[i] == '<' && utils->word[i + 1] == '<')
			return (HERE_DOC);
	}
	return (-1);
}

void	redir_special(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '>')
	{
		update_word('>', &utils->word);
		utils->i++;
	}
	else if (c == '<')
	{
		update_word('<', &utils->word);
		utils->i++;
		if (utils->str[utils->i] == '-')
		{
			update_word('-', &utils->word);
			utils->i++;
		}
	}
}

static void	carac_special(char c, t_utils_lexer *utils, t_main *main)
{
	if (utils->sing_q == 1 || (utils->double_q == 1) || 
		(utils->echap == 1 && c != ' '))
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', &utils->word);
		update_word(c, &utils->word);
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
		if ((utils->str[utils->i] == '>' && utils->str[utils->i + 1] == '>')
			|| (utils->str[utils->i] == '<' && utils->str[utils->i + 1] == '<'))
			redir_special(utils->str[utils->i], utils, main);
		malloc_element(reconize_carac_spec(utils), utils, main);
	}
}

static void	is_fd_redir(char c, t_utils_lexer *util, t_main *main)
{
	int	i;

	if (util->sing_q == 1 || util->double_q == 1 || util->echap == 1)
	{
		if (util->double_q == 1 && util->echap == 1)
			update_word('\\', &util->word);
		update_word(c, &util->word);
	}
	else
	{
		i = util->i;
		while (ft_isdigit(util->str[i]))
			i++;
		if (util->str[i] == '>' || util->str[i] == '<')
		{
			while (util->i < i)
				update_word(util->str[util->i++], &util->word);
			update_word(util->str[util->i], &util->word);
			if (util->str[util->i + 1] == '>' || util->str[util->i + 1] == '<')
				redir_special(util->str[util->i], util, main);
			malloc_element(reconize_carac_spec(util), util, main);
		}
		else
			update_word(c, &util->word);
	}
}

void	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\0')
		return ;
	else if (c == '\\')
		return (backslash(c, utils, main));
	else if (c == '\'')
		return (single_quotes(c, utils, main));
	else if (c == '"')
		return (double_quotes(c, utils, main));
	else if (c == '$')
		return (dollar(c, utils, main));
	else if (ft_isdigit(c) == TRUE)
		return (is_fd_redir(c, utils, main));
	else if (c == '>' || c == '<' || c == '|' || c == ' ' || c == ';')
		return (carac_special(c, utils, main));
	else
	{
		if (utils->double_q == 1 && utils->echap == 1)
			update_word('\\', &utils->word);
		update_word(c, &utils->word);
	}
}
