#include "minishell.h"

void	update_main_lexer(t_type_lex type, t_list **save)
{
	t_list		*tmp_lst;
	t_lexer		*tmp_lex;

	tmp_lex = (*save)->content;
	while ((*save) != NULL && tmp_lex->type != type)
	{
		(*save) = (*save)->next;
		if ((*save) != NULL)
			tmp_lex = (*save)->content;
	}
	if ((*save) != NULL)
	{
		tmp_lst = (*save);
		(*save) = (*save)->next;
		tmp_lst->next = NULL;
	}
}

void	create_cmd(t_main *main)
{
	t_list		*param_lst;
	t_list		*save;

	param_lst = NULL;
	save = main->lexer;
	while (main->lexer != NULL)
	{
		update_main_lexer(NEW_COMMAND, &save);
		create_param_cmd(&param_lst, main);
		cmd_exec(param_lst, main);
		ft_lstclear(&param_lst, free_param_cmd);
		main->lexer = save;
	}
}

void	loop(t_main *main)
{
	while (42)
	{
		if (main->line != NULL)
		{
			free(main->line);
			main->line = NULL;
		}
		main->line = readline("bash_des_freros$ ");
		if (main->line && *main->line)
			add_history (main->line);
		tokenization(main->line, 0, main);
		create_cmd(main);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_main	main;

	(void)argv;
	setbuf(stdout, NULL);
	if (argc != 1)
		quit_prog("minishell as to be launch without args\n", &main);
	ft_bzero(&main, sizeof(t_main));
	main.env = cpy_env(env, &main);
	main.home_path = save_path_home(main.env, &main);
	init_cmd_fct(&main);
	loop(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
