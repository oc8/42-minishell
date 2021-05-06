/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdoenlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:47:57 by tdoenlen          #+#    #+#             */
/*   Updated: 2021/02/03 16:13:23 by tdoenlen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_start_too_big(char const *s, unsigned int start)
{
	unsigned long int	size;

	size = 0;
	while (s[size])
		size++;
	return (size <= start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*ret;
	unsigned long int	i;

	i = 0;
	if (!s)
		return (0);
	if (is_start_too_big(s, start))
	{
		ret = malloc(sizeof(char));
		*ret = 0;
		return (ret);
	}
	while (s[start + i] && i < len)
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	while (s[start + i] && i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
