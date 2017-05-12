/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 11:43:58 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:10:28 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *))
{
	t_list	*ret;
	t_list	*ret_last;

	ret = f(lst);
	ret_last = ret;
	if (!(ret) || !(lst))
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		ret_last->next = f(lst);
		if (!(ret_last->next))
			return (NULL);
		ret_last = ret_last->next;
	}
	return (ret);
}
