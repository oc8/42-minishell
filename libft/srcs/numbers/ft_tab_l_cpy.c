/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_l_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:55:58 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/06 15:18:48 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

long	*ft_tab_l_cpy(long *tabl, int nbr)
{
	long	*tab_cpy;

	if (!nbr)
		return (0);
	tab_cpy = ft_calloc(nbr, sizeof(long));
	while (--nbr >= 0)
		tab_cpy[nbr] = tabl[nbr];
	return (tab_cpy);
}
