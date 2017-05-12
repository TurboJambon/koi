/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:10:08 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/04 17:17:06 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *ts1;
	unsigned char *ts2;

	ts1 = (unsigned char*)s1;
	ts2 = (unsigned char*)s2;
	while (n && *ts1 == *ts2)
	{
		ts1++;
		ts2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*ts1 - *ts2);
}
