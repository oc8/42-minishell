/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_param_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:54:03 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/31 22:06:56 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var_info	*contain_var(t_main *main)
{
	t_list		*index;
	// t_list		*previous;
	t_lexer		*tmp;
	t_list		*next;
	t_var_info	*var_info;
	int i;

	i = 1;
	// ft_bzero(&var_info, sizeof(t_var_info));
	// var_info->previous = NULL;
	index = main->lexer;
	var_info = malloc(sizeof(t_var_info));
	if (!var_info)
		quit_prog("var_info malloc creation", main);
	while (index!= NULL)
	{
		tmp = index->content;
		if (tmp->type == VAR_ENV)
		{
			var_info->i_lst = i;
			var_info->value = ft_strdup_no_list(tmp->value);
			if (i == 1)
			{
				next = index->next;
				free_lexer(index);
				main->lexer = main->lexer->next;

			}
			else
			{
				next = index->next;
				free_lexer(index);
				var_info->previous->next = next;
			}
			return (var_info);
			// return (previous)
		}
		var_info->previous = index;
		index = index->next;
		i++;
	}
	free(var_info);
	return (NULL);
}

void	create_param_cmd(t_param_cmd *param, t_main *main)
{
	t_var_info	*var_info;
	char		*to_treat;
	
	to_treat = NULL;
	var_info = contain_var(main);
	while (var_info != NULL)
	{
		remplace_var_value(&to_treat, var_info->value, main);
		printf("to_treat = %s\n", to_treat);
		tokenization(to_treat, var_info->i_lst, main);
		free(var_info->value);
		free(var_info);
		free(to_treat);
		var_info = contain_var(main);
	}
	define_text_types(main);
	// print_lexer(main);
	fill_struct(param, main);
	print_struct_cmd(param);
}