/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:51:10 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/10 18:26:30 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fail(char *error_str, t_main *main)
{
	write(1, "Error : ", 8);
	write(1, error_str, ft_strlen(error_str));
	if (main->lexer != NULL)
		ft_lstclear(&main->lexer, free);
	ft_lstclear(&main->free, free);
	exit(1);
}