/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_secure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:59:00 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/19 14:25:04 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*calloc_secure(t_list **malloc_lst, size_t space, \
			void (*quit)(char *, t_main *), t_main *main)
{
	void	*rs;
	t_list	*content;

	rs = ft_calloc(1, space);
	if (!rs)
		quit("error malloc() in calloc_lst()", main);
	if (!*malloc_lst)
	{
		*malloc_lst = ft_lstnew(rs);
		if (!*malloc_lst)
			quit("error malloc() in calloc_lst()", main);
	}
	else
	{
		content = ft_lstnew(rs);
		if (!content)
			quit("error malloc() in calloc_lst()", main);
		ft_lstadd_front(malloc_lst, content);
	}
	return (rs);
}
