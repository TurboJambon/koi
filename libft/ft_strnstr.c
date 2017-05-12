/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:50:01 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:22:28 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	strn;
	char	*str1;
	char	*str2;

	if (!*s2)
		return ((void *)s1);
	while (n-- && *s1)
	{
		if (*s1 == *s2)
		{
			strn = n;
			str1 = (void *)s1 + 1;
			str2 = (void *)s2 + 1;
			while (strn-- && *str1 && *str2 && *str1 == *str2)
			{
				++str1;
				++str2;
			}
			if (!*str2)
				return ((void *)s1);
		}
		s1++;
	}
	return (NULL);
}
