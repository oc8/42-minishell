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
		rl_redisplay();
	}
	else if (signum == SIGKILL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (signum == SIGQUIT)
	{
		// printf("Quit: 3\n");
	}
}

// t_js	*getter_job(void)
// {
// 	static t_js job = (t_js) {.first_job = 0, .shell_pgid = 0,
// 	{ .c_iflag = 0, .c_oflag = 0, .c_cflag = 0, .c_lflag = 0 },
// 	.shell_terminal = 0, .shell_is_interactive = 0};
// 	return (&job);
// }

// void	sig_action(int sig)
// {
// 	// ft_putchar_fd('\r', 1);
// 	// ft_putchar_fd('\r', 1);
// 	if (sig == SIGINT)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	else if (sig == SIGKILL)
// 	{
// 		printf("exit\n");
// 		exit(0);
// 	}
// }

int	main(int argc, char *argv[], char *env[])
{
	t_main	main;

	(void)argv;
	setbuf(stdout, NULL);
	if (argc != 1)
		quit_prog("minishell as to be launch without args\n", &main);
	ft_bzero(&main, sizeof(t_main));
	global.main = &main;
	signal(SIGINT, &sig_action);
	signal(SIGQUIT, &sig_action);
	signal(SIGKILL, &sig_action);
	main.env = cpy_env(env, &main);
	reset_var(&main);
	main.home_path = save_path_home(main.env, &main);
	init_cmd_fct(&main);
	main.save_fd[0] = dup(0);
	main.save_fd[1] = dup(1);
	// print_env(&main);
	loop(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
