/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:39:38 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/04 14:51:26 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
		i++;
	}
	return (spoups);
}
