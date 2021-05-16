/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:11:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/11 19:05:51 by odroz-ba         ###   ########lyon.fr   */
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
	
	printf("Lexer :\n");
	iter = main->lexer;
	while (iter != NULL)
	{
		tmp = iter->content;
		printf("| Value = %s|\n", tmp->value);
		if (tmp->type == 0)
			printf("| Type = COMMAND|\n");
		else if (tmp->type == 1)
			printf("| Type = OPERATOR|\n");
		else if (tmp->type == 2)
			printf("| Type = ARGUMENT|\n");
		printf("\n");
		iter = iter->next;
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
	init_cmd_fct(&main);
	while (ft_strncmp_minishell(main.line, "exit", 5))
	{
		if (main.line != NULL)
			free(main.line);
		get_operator_command(&main);
		pars_line(&main);
		// print_line(&main);
		print_lexer(&main);
		test_cmd_exec(&main);
		if(main.lexer != NULL)
			ft_lstclear(&main.lexer, free_lexer);
	}
	print_histo(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
