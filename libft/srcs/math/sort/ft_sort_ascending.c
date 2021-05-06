/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_ascending.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:16:55 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/03 14:16:56 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_switch_long(long *v1, long *v2)
{
	long	temp;

	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void	ft_sort_ascending(long *lst, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (++i < size)
	{
		j = 0;
		while (++j < size)
			if (lst[j - 1] > lst[j])
				ft_switch_long(&lst[j - 1], &lst[j]);
	}
}
