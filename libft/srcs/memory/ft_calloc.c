/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:28:53 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/19 14:26:01 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbr, size_t size)
{
	void	*ptr;

	if (nbr == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nbr * size);
	if (!ptr)
		return (0);
	ft_memset((unsigned char *)ptr, 0, nbr * size);
	return (ptr);
}
