/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 18:13:25 by David             #+#    #+#             */
/*   Updated: 2016/11/12 12:13:00 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*spips;
	unsigned char	*spoups;

	spips = (unsigned char*)src;
	spoups = (unsigned char*)dest;
	i = 0;
	while (i < n)
	{
		spoups[i] = spips[i];
		if (spips[i] == (unsigned char)c)
			return ((void *)spoups + i + 1);
		i++;
	}
	return (NULL);
}
