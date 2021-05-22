/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:11:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/22 13:49:13 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_histo(t_main *main)
{
	t_list *tmp;

	tmp = main->histo;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	print_lexer(t_main *main)
{
	t_lexer	*tmp;
	t_list	*iter;
	
	printf("Lexer , size = %d : \n", ft_lstsize(main->lexer));
	iter = main->lexer;
	while (iter != NULL)
	{
		tmp = iter->content;
		printf("Value = |%s|\n", tmp->value);
		if (tmp->type == COMMAND)
			printf("Type = COMMAND\n");
		else if (tmp->type == ARGUMENT)
			printf("Type = ARGUMENT\n");
		else if (tmp->type == NEW_COMMAND)
			printf("Type = NEW_COMMAND\n");
		else if (tmp->type == FILE_NAME)
			printf("Type = FILE_NAME\n");
		else if (tmp->type == REDIRECTION)
			printf("Type = REDIRECTION\n");
		printf("\n");
		iter = iter->next;
	}
}

void	print_env(t_main *main)
{
	size_t	i;

	i = -1;
	while (main->env[++i] != NULL)
		printf("%s\n", main->env[i]);
}

void	loop(t_main *main)
{
	while (ft_strncmp_minishell(main->line, "exit", 5))
	{
		if (main->line != NULL)
			free(main->line);
		get_operator_command(main);
		// pars_line(&main);
		// print_line(&main);
		// print_lexer(&main);
		test_cmd_exec(main);
		if(main->lexer != NULL)
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
	main.env = env;
	// print_env(&main);
	init_cmd_fct(&main);
	loop(&main);
	print_histo(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
