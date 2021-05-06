/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:32:29 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/02 15:28:19 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(t_list **malloc, const char *s1)
{
	char	*s1copy;
	int		i;

	s1copy = ft_calloc_lst(malloc, ft_strlen(s1) + 1, sizeof(*s1copy));
	if (!s1copy)
		return (0);
	i = -1;
	while (s1[++i])
		s1copy[i] = s1[i];
	s1copy[i] = '\0';
	return (s1copy);
}
