/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:11:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/06 19:16:49 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_histo(t_res *res)
{
	t_list *tmp;

	tmp = res->histo;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int	main(int argc, char *argv[])
{
	t_res	res;
	
	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	ft_bzero(&res, sizeof(t_res));
	while (ft_strncmp_minishell(res.line, "exit", 5))
	{
		if (res.line != NULL)
			free(res.line);
		get_operator_command(&res);
	}
	print_histo(&res);
	free(res.line);
	ft_lstclear(&res.free, free);
	return (0);
}
