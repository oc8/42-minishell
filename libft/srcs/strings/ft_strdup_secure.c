/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_secure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:20:50 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/17 16:13:58 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strdup_secure(t_list **malloc, const char *s1, \
			void (*quit)(char *, t_main *), t_main *main)
{
	char	*s1copy;
	int		i;

	s1copy = calloc_secure(malloc, ft_strlen(s1) + 1 * sizeof(*s1copy), \
		quit, main);
	if (!s1copy)
		quit("malloc in strdup_secure()", main);
	i = -1;
	while (s1[++i])
		s1copy[i] = s1[i];
	s1copy[i] = '\0';
	return (s1copy);
}
