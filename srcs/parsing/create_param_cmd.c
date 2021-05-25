/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_param_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:54:03 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/25 21:11:15 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		contain_var(t_main *main)
{
	t_list	*index;
	t_lexer	*tmp;
	int i;

	i = 0;
	index = main->lexer;
	while (index!= NULL)
	{
		tmp = index->content;
		if (tmp->type == VAR_ENV)
			return (i);
		index = index->next;
		i++;
	}
	return (-1);
}



void	create_param_cmd(t_param_cmd *param, t_main *main)
{
	int	var_index;
	int	i;
	
	print_lexer(main);
	// var_index = contain_var(main);
	// while (var_index != -1)
	// {
	// 	while ()
	// 	add_var(var_index, main);

	// }

}