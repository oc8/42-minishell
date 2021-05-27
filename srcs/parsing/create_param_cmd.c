/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_param_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:54:03 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 20:52:45 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var_info	*contain_var(t_main *main)
{
	t_list		*index;
	t_lexer		*tmp;
	t_var_info	*var_info;
	int i;

	i = 1;
	index = main->lexer;
	while (index!= NULL)
	{
		tmp = index->content;
		if (tmp->type == VAR_ENV)
		{
			var_info = malloc(sizeof(t_var_info));
			if (!var_info)
				quit_prog("var_info malloc creation", main);
			var_info->i_lst = i;
			var_info->value = ft_strdup_no_list(tmp->value);
			return (var_info);
		}
		index = index->next;
		i++;
	}
	return (NULL);
}

void	create_param_cmd(t_param_cmd *param, t_main *main)
{
	t_var_info	*var_info;
	
	// var_info = contain_var(main);
	// while (var_info != NULL)
	// {
	// 	tokenization(var_info->value, var_info->i_lst, main);
	// 	free(var_info->value);
	// 	free(var_info);
	// 	var_info = contain_var(main);
	// }
	define_text_types(main);
	print_lexer(main);
	fill_struct(param, main);
	print_struct_cmd(param);
}