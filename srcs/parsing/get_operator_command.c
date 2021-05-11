/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:43:55 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/11 17:16:57 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_operator_command(t_main *main)
{
	int		ret;
	t_list	*new_elem;
	char	*new_line;

	write(1, "bash_des_freros$ ", 17);
	ret = get_next_line(0, &main->line);
	if (ret == -1)
	{
		free(main->line);
		quit_prog("Error read operator command\n", main);
	}
	new_line = ft_strdup(&main->free, main->line);
	new_elem = ft_calloc_lst(&main->free, 1, sizeof(t_list));
	new_elem->content = new_line;
	ft_lstadd_front(&main->histo, new_elem);
}