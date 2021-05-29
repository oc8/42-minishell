/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:53:12 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/28 14:55:27 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_redirection(const char *nptr, t_type_lex type)
{
	long long	rs;
	int			i;

	i = 0;
	if (!ft_isdigit(nptr[i]))
	{
		if (type == REDIR_INPUT)
			rs = 0;
		else if (type == REDIR_OUTPUT || type == APPEND_REDIR_OUTPUT)
			rs = 1;
		return (rs);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		rs = rs * 10 + (nptr[i++] - '0');
		if (rs > INT_MAX)
			return (INT_MAX);
	}
	return (rs);
}
