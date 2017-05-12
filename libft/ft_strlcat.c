/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:10:17 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/07 11:19:11 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	result;

	i = 0;
	j = 0;
	result = ft_strlen(src);
	while (dest[i] && i < n)
		i++;
	if (n > 0)
	{
		while (src[j] && i < n - 1)
		{
			dest[i++] = src[j++];
		}
	}
	if (j > 0)
	{
		dest[i] = '\0';
		return (result + i - j);
	}
	return (result + i);
}
