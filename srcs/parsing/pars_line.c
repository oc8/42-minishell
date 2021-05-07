/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:52:39 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/07 15:10:02 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reconize(t_main *main)
{
	int i;

	i = -1;
	reconize_commands(main);
	while (main->line[++i])
	{
	}
}

void	lexer(t_main *main)
{
	int i;

	i = -1;
	reconize_commands(main);
	while (main->line[++i])
	{
	}
}

void	pars_line(t_main *main)
{
	lexer(main);
}