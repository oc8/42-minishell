/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdoenlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:38:40 by tdoenlen          #+#    #+#             */
/*   Updated: 2021/02/03 16:12:38 by tdoenlen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_in_str(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static unsigned long int	calc_end(unsigned long int i,
	char const *s1, char const *set)
{
	if (!(s1[i]))
		return (i - 1);
	while (s1[i])
		i++;
	i--;
	while (is_in_str(s1[i], (char *)set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned long int	i;
	unsigned long int	start;
	unsigned long int	end;
	char				*ret;

	i = 0;
	if (!s1 || !set)
		return (0);
	while (is_in_str(s1[i], (char *)set))
		i++;
	start = i;
	end = calc_end(i, s1, set);
	ret = malloc(((end - start) + 2) * sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	while (i < end - start + 1)
	{
		ret[i] = s1[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
