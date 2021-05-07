/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:40:24 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/07 16:10:43 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_main *main)
{
	int i;
	int w_count;
	char *word;
	
	word =  NULL;
	i = -1;
	while (main->line[++i])
	{
		w_count= 0;
		while (end_word(main) == FALSE)
		{
			i++;
			w_count++;
			
		}
		
		// if (main->line[++i] == ' ')
		// {
		// 	if (word)
		// 	i++;
		// }
		// else 
	}
}