/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:09:46 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/18 16:25:55 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*strdst;
	unsigned char	*strsrc;
	int				i;

	i = 0;
	strdst = (unsigned char *)dst;
	strsrc = (unsigned char *)src;
	while (n--)
	{
		strdst[i] = strsrc[i];
		if (strsrc[i] == (unsigned char)c)
			return (strdst + i + 1);
		i++;
	}
	return (0);
}
