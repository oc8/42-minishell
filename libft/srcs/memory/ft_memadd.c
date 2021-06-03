/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:54:54 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/24 15:03:37 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memadd(void *src, size_t old_size, size_t new_size, size_t space)
{
	char	*new;
	size_t	i;

	new = ft_calloc(new_size + 1, space);
	i = 0;
	while (i < old_size * space && i < new_size * space)
	{
		new[i] = ((char *)src)[i];
		i++;
	}
	new[i] = 0;
	// free(src); // leaks ??
	return (new);
}
