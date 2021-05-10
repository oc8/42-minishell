/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:11:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/10 18:18:05 by odroz-ba         ###   ########lyon.fr   */
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

int	main(int argc, char *argv[])
{
	t_main	main;

	(void)argv;
	setbuf(stdout, NULL);	
	if (argc != 1)
		fail("minishell as to be launch without args\n", &main);
	ft_bzero(&main, sizeof(t_main));
	while (ft_strncmp_minishell(main.line, "exit", 5))
	{
		if (main.line != NULL)
			free(main.line);
		if(main.lexer != NULL)
			ft_lstclear(&main.lexer, free);
		get_operator_command(&main);
		// parse_line(&main);
		// print_line(&main);
		cmd_exec(&main);
	}
	print_histo(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
