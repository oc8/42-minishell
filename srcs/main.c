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
	if (!main->lexer)
		g_global.exit_status = 0;
	while (main->lexer != NULL)
	{
		update_main_lexer(NEW_COMMAND, &save);
		create_param_cmd(&param_lst, main);
		signal(SIGQUIT, &sig_action);
		g_global.in_cmd = 1;
		cmd_exec(param_lst, main);
		signal(SIGQUIT, SIG_IGN);
		g_global.in_cmd = 0;
		ft_lstclear(&param_lst, free_param_cmd);
		main->lexer = save;
	}
}

void	loop(t_main *main)
{
	char	*prompt;

	while (42)
	{
		if (main->line != NULL)
		{
			free(main->line);
			main->line = NULL;
		}
		prompt = location(main);
		main->line = readline(prompt);
		if (!main->line)
			main->line = ft_strdup_no_list("exit");
		free(prompt);
		if (main->line && *main->line)
			add_history(main->line);
		tokenization(main->line, 0, main);
		create_cmd(main);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
	}
}

void	sig_action(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_global.in_cmd)
		{
			g_global.exit_status = 1;
			rl_redisplay();
		}
		else
			g_global.exit_status = 130;
	}
	if (signum == SIGQUIT)
	{
		if (g_global.in_cmd)
		{
			printf("Quit: 3\n");
			g_global.exit_status = 131;
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_main	main;

	(void)argv;
	if (argc != 1)
		quit_prog("minishell as to be launch without args\n", &main);
	ft_bzero(&main, sizeof(t_main));
	signal(SIGINT, &sig_action);
	signal(SIGQUIT, SIG_IGN);
	main.env = cpy_env(env, &main);
	reset_var(&main);
	main.home_path = save_path_home(main.env, &main);
	init_cmd_fct(&main);
	main.save_fd[0] = dup(0);
	main.save_fd[1] = dup(1);
	loop(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
