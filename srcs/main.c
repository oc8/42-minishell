#include "minishell.h"

void	print_histo(t_main *main)
{
	t_list *tmp;

	tmp = main->histo;
	while (tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_env(t_main *main)
{
	size_t	i;

	i = -1;
	while (main->env[++i] != NULL)
		printf("%s\n", main->env[i]);
}

void	update_main_lexer(t_type_lex type, t_list **save, t_main *main)
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
	// t_list		*tmp_lst;
	// t_lexer		*tmp_lex;

	param_lst = NULL;
	save = main->lexer;
	while (main->lexer != NULL)
	{
		update_main_lexer(NEW_COMMAND, &save, main);
		create_param_cmd(&param_lst, main);
		// exec_cmd(&param, main);				//  --> PARTIE COMMAND OCEAN
		ft_lstclear(&param_lst, free_param_cmd);
		main->lexer = save;
	}
}

void	loop(t_main *main)
{
	while (ft_strncmp_minishell(main->line, "exit", 5))
	{
		if (main->line != NULL)
			free(main->line);
		get_operator_command(main);
		// test_cmd_exec(main);
		tokenization(main->line, 0, main);
		// print_lexer(main);
		create_cmd(main);
		if (main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
	}
}

char	**cpy_env(char *env[], t_main *main)
{
	char	**rs;
	size_t	i;
	size_t	len;

	len = ft_doublelen((const void **)env) + 1;
	main->nbr_env = len - 1;
	rs = ft_calloc_lst(&main->free, len, sizeof(char *));
	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]) + 1;
		rs[i] = ft_calloc_lst(&main->free, len, sizeof(char));
		ft_strlcpy(rs[i], env[i], len);
		// printf("%s | %s : %zu\n", env[i], rs[i], len);
		i++;
	}
	rs[i] = 0;
	return (rs);
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
	init_cmd_fct(&main);
	// print_env(&main);
	loop(&main);
	// print_histo(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
