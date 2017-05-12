/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:50:01 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:23:15 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	char	*tmp;

	if (*s2 == '\0')
		return ((char *)s1);
	if (ft_strlen(s2) > ft_strlen(s1))
		return (NULL);
	tmp = (char *)s1;
	while (*tmp)
	{
		if (*tmp == *s2)
		{
			i = 0;
			while (tmp[i] == s2[i] && s2[i])
				i++;
			if (s2[i] == '\0')
				return (tmp);
		}
		tmp++;
	}
	return (NULL);
}
