#include "minishell.h"

static void	backslash(char c, t_utils_lexer *utils, t_main *main)
{
	if ((utils->double_q == 0 && utils->sing_q == 0 && utils->echap == 0)
		|| (utils->double_q == 1 && utils->echap == 0))
		utils->echap = 2;
	else
		update_word(c, &utils->word);
}

static void	quotes(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\'')
	{
		if (utils->double_q == 1 || utils->echap == 1)
		{
			if (utils->double_q == 1 && utils->echap == 1)
				update_word('\\', &utils->word);
			update_word(c, &utils->word);
		}
		else if (utils->sing_q == 0 && utils->double_q == 0)
		{
			utils->sing_q = 1;
			update_word('\0', &utils->word);
		}
		else if (utils->sing_q == 1)
			utils->sing_q = 0;
	}
	else if (c == '"')
	{
		if (utils->sing_q == 1 || utils->echap == 1)
			update_word(c, &utils->word);
		else if (utils->double_q == 0 && utils->sing_q == 0)
		{
			utils->double_q = 1;
			update_word('\0', &utils->word);
		}
		else if (utils->double_q == 1)
			utils->double_q = 0;
	}
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
			return (REDIR_IN);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '\0')
			return (REDIR_OUT);
		else if (utils->word[i] == '>' && utils->word[i + 1] == '>')
			return (APP_REDIR_OUT);
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
	}
	else if (c == ' ')
	{
		// if (!utils->word && utils->start_word != utils->i)
		// 	update_word('\0', &utils->word);
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
	}
	else
	{
		i = utils->i;
		while (ft_isdigit(utils->str[i]))
			i++;
		if (utils->str[i] == '>' || utils->str[i] == '<')
		{
			while (utils->i < i)
				update_word(utils->str[utils->i++], &utils->word);
			update_word(utils->str[utils->i], &utils->word);
			if (utils->str[utils->i + 1] == '>')
				update_word(utils->str[utils->i++], &utils->word);
			malloc_element(reconize_carac_spec(utils), utils, main);
		}
		else
			update_word(c, &utils->word);
	}
}

void	check_caracter_lex(char c, t_utils_lexer *utils, t_main *main)
{
	if (c == '\0')
		return ;
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
	}
}
