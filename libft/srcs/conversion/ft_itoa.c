/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:43:33 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/04/23 18:18:27 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_neg(long *n_long, int *count)
{
	if (*n_long < 0)
	{
		*n_long *= -1;
		*count = 1;
		return (0);
	}
	return (1);
}

static void	ft_init(long *cpy, int *count, char *flag, long n_long)
{
	*count = 0;
	*flag = ft_check_neg(&n_long, count);
	*cpy = n_long;
	*cpy /= 10;
}

char	*ft_itoa(int n)
{
	long	cpy;
	int		count;
	char	*rs;
	char	flag;
	long	n_long;

	n_long = (long)n;
	ft_init(&cpy, &count, &flag, n_long);
	while (cpy)
	{
		cpy /= 10;
		count++;
	}
	rs = malloc(sizeof(char) * count + 2);
	if (!rs)
		return (0);
	if (flag == 0)
		rs[0] = '-';
	rs[count + 1] = '\0';
	while (rs + count + flag > rs)
	{
		rs[count--] = n_long % 10 + '0';
		n_long /= 10;
	}
	return (rs);
}
