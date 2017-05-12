/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:12:55 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/11 14:11:27 by David            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *next;
	t_list *lst;

	if (alst == NULL)
		return ;
	lst = *alst;
	while (lst)
	{
		next = lst->next;
		ft_lstdelone(&lst, del);
		lst = next;
	}
	*alst = NULL;
}
