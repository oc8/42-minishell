/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:16:20 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/10 18:28:57 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(void *s)
{
	t_lexer	*lexer;
	
	lexer = (t_lexer*)s;
	free(lexer->value);
	free(lexer);
}