/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_median.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:39:14 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/19 16:13:22 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_median(long *tabl, unsigned int size)
{
	long	*tab_cpy;
	long	median;

	tab_cpy = 0;
	tab_cpy = ft_memcpy(tab_cpy, tabl, size);
	ft_sort_ascending(tab_cpy, size);
	median = tab_cpy[size / 2 - 1];
	free(tab_cpy);
	return (median);
}
