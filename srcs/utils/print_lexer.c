/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:53:01 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/26 17:14:30 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (tmp->type == TO_DEFINE)
			printf("Type = TO_DEFINE\n");
		else if (tmp->type == VAR_ENV)
			printf("Type = VAR_ENV\n");
		else if (tmp->type == SEPARATOR)
			printf("Type = SEPARATOR\n");
		else if (tmp->type == PIPE)
			printf("Type = PIPE\n");
		printf("\n");
		iter = iter->next;
	}
}