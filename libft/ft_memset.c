/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:21:35 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/03 15:38:48 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*spips;

	spips = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		spips[i] = c;
		i++;
	}
	return ((void *)spips);
}
