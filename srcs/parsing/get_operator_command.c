/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:43:55 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/06 19:26:49 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_operator_command(t_res *res)
{
	int		ret;
	t_list	*new_elem;
	char	*new_line;

	write(1, "bash_des_freros$ ", 17);
	ret = get_next_line(0, &res->line);
	if (ret == -1)
	{
		free(res->line);
		fail("Error read operator command\n", res);
	}
	new_line = ft_strdup(&res->free, res->line);
	// printf("new_line = %s\n", new_line);
	new_elem = ft_calloc_lst(&res->histo, 1, sizeof(t_list));
	new_elem->content = new_line;
	ft_lstadd_front(&res->histo, new_elem);
}