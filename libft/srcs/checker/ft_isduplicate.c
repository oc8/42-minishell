/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isduplicate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:01:21 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/04/25 17:52:41 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_check(long *lst, int i, int size)
{
	long	nbr;

	nbr = lst[i];
	while (++i < size)
		if (lst[i] == nbr)
			return (1);
	return (0);
}

/*
**	check if the list contains duplicate
*/
char	ft_isduplicate(long *lst, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (ft_check(lst, i, size))
			return (1);
	return (0);
}
