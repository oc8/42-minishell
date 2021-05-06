/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdoenlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:02:09 by tdoenlen          #+#    #+#             */
/*   Updated: 2021/02/03 16:02:41 by tdoenlen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long int	len(char const *str)
{
	unsigned long int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long int	s1_i;
	unsigned long int	s2_i;
	char				*ret;

	s1_i = 0;
	s2_i = 0;
	if (!s1 || !s2)
		return (0);
	ret = malloc((len(s1) + len(s2) + 1) * sizeof(char));
	if (!ret)
		return (0);
	while (s1[s1_i])
	{
		ret[s1_i] = s1[s1_i];
		s1_i++;
	}
	while (s2[s2_i])
	{
		ret[s1_i + s2_i] = s2[s2_i];
		s2_i++;
	}
	ret[s1_i + s2_i] = 0;
	return (ret);
}
