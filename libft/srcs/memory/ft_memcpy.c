/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:45:05 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/04/23 17:26:12 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*strdst;
	const char	*strsrc;

	if (src == dst)
		return (dst);
	strdst = dst;
	strsrc = src;
	while (n--)
	{
		*strdst = *strsrc;
		strdst++;
		strsrc++;
	}
	return (dst);
}
