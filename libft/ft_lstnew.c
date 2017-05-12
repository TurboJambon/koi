/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:31:10 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:12:41 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;
	void	*lcontent;
	size_t	lsize;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		lcontent = ft_memalloc(content_size);
		lsize = content_size;
		ft_memcpy(lcontent, content, content_size);
		lst->content = lcontent;
		lst->content_size = lsize;
	}
	else
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	lst->next = NULL;
	return (lst);
}
