/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:23 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/04/23 17:26:38 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;
	char	*str;
	int		i;

	cc = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != cc && str[i])
		i++;
	if (cc == '\0')
		return (&str[i]);
	if (str[i] == '\0')
		return (0);
	return (&str[i]);
}
