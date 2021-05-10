/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:32:29 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/10 17:11:20 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_no_list(const char *s1)
{
	char	*s1copy;
	int		i;

	s1copy = malloc(ft_strlen(s1) + 1);
	if (!s1copy)
		return (0);
	i = -1;
	while (s1[++i])
		s1copy[i] = s1[i];
	s1copy[i] = '\0';
	return (s1copy);
}
