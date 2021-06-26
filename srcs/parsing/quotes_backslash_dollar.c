#include "minishell.h"

void	backslash(char c, t_utils_lexer *utils, t_main *main)
{
	if ((utils->double_q == 0 && utils->sing_q == 0 && utils->echap == 0)
		|| (utils->double_q == 1 && utils->echap == 0))
		utils->echap = 2;
	else
		update_word(c, &utils->word);
}

void	single_quotes(char c, t_utils_lexer *utils, t_main *main)
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

void	double_quotes(char c, t_utils_lexer *utils, t_main *main)
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

static void	bash_script(t_utils_lexer *utils, t_main *main)
{
	char	*exit_status;
	int		i;

	exit_status = ft_itoa(global.exit_status);
	i = -1;
	while (exit_status[++i])
		update_word(exit_status[i], &utils->word);
	free(exit_status);
	utils->i++;
}

void	dollar(char c, t_utils_lexer *utils, t_main *m)
{
	if (utils->sing_q == 1 || utils->echap == 1 || is_here_doc(m))
		update_word(c, &utils->word);
	else
	{
		if (utils->str[utils->i + 1] == '"' || utils->str[utils->i + 1] == '\'')
			return ;
		if (utils->str[utils->i + 1] == '?')
		{
			bash_script(utils, m);
			return ;
		}
		if (!ft_isalpha(utils->str[utils->i + 1])
			&& utils->str[utils->i + 1] != '_' && utils->str[utils->i + 1])
		{
			utils->i++;
			update_word(utils->str[utils->i], &utils->word);
			return ;
		}
		update_word('$', &utils->word);
		if (utils->str[utils->i + 1])
			utils->var_env = 1;
	}
}
