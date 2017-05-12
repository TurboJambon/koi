/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:08:35 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:20:48 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char *position;

	position = NULL;
	while (*s)
	{
		if (*s == (char)c)
			position = (char*)s;
		s++;
	}
	if (*s == (char)c)
		return ((char*)s);
	else
		return (position);
}
