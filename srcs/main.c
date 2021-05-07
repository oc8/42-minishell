/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:11:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/07 14:09:53 by tdayde           ###   ########lyon.fr   */
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
	if (argc != 1)
		fail("minishell as to be launch without args\n", &main);
	setbuf(stdout, NULL);
	ft_bzero(&main, sizeof(t_main));
	while (ft_strncmp_minishell(main.line, "exit", 5))
	{
		if (main.line != NULL)
			free(main.line);
		get_operator_command(&main);
		parse_line(&main);
		print_line(&main);
	}
	print_histo(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
