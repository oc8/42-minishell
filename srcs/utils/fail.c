/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:51:10 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/06 17:05:21 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fail(char *error_str, t_res *res)
{
	write(1, error_str, ft_strlen(error_str));
	ft_lstclear(&res->free, free);
	exit(1);
}