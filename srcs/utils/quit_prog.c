/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:51:10 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/11 17:19:16 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_prog(char *str, t_main *main)
{
	if (str)
	{
		ft_putstr_fd("\033[31mError : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\n\033[0m", STDERR_FILENO);
	}
	if (main->lexer != NULL)
		ft_lstclear(&main->lexer, free);
	// if (main->histo != NULL)
	// 	ft_lstclear(&main->histo, free);
	if (main->file)
		close(main->file);
	ft_lstclear(&main->free, free);
	if (str)
		exit(1);
	exit(0);
}
