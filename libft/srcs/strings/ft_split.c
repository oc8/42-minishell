/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdoenlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 15:20:18 by tdoenlen          #+#    #+#             */
/*   Updated: 2021/02/03 16:00:27 by tdoenlen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_free_ret(char **ret, unsigned long int w)
{
	while (w)
		free(ret[--w]);
	free(ret);
	return (1);
}

static size_t	ft_count_chars(char const *s, char c, unsigned long int i)
{
	size_t	nb_c;

	nb_c = 0;
	while (s[i + nb_c] != c && s[i + nb_c])
		nb_c++;
	return (nb_c);
}

static char	ft_fill_ret(char **ret,
	char const *s, char c, unsigned long int nb_w)
{
	unsigned long int	i;
	unsigned long int	j;
	unsigned long int	w;

	i = 0;
	w = 0;
	while (w < nb_w)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			ret[w] = malloc((ft_count_chars(s, c, i) + 1) * sizeof(char));
			if (!(ret[w]))
				return (ft_free_ret(ret, w));
			j = 0;
			while (s[i] != c && s[i])
				ret[w][j++] = s[i++];
			ret[w++][j] = 0;
		}
	}
	ret[nb_w] = 0;
	return (0);
}

static unsigned long int	ft_count_words(char const *s, char c)
{
	unsigned long int	nb_w;
	unsigned long int	i;

	nb_w = 1;
	if (*s == c || !*s)
		nb_w = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i])
				i++;
			if (s[i])
				nb_w++;
		}
		else
			i++;
	}
	return (nb_w);
}

char	**ft_split(char const *s, char c)
{
	unsigned long int	nb_w;
	char				**ret;

	if (!s)
		return (0);
	nb_w = ft_count_words(s, c);
	ret = malloc((nb_w + 1) * sizeof(char *));
	if (!ret || ft_fill_ret(ret, s, c, nb_w))
		return (0);
	return (ret);
}
