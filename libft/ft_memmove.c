/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:43:01 by dchirol           #+#    #+#             */
/*   Updated: 2017/01/21 19:20:53 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*srcbis;
	unsigned char	*destbis;

	srcbis = (unsigned char*)src;
	destbis = (unsigned char*)dest;
	if (srcbis < destbis)
	{
		srcbis = srcbis + n - 1;
		destbis = destbis + n - 1;
		while (n)
		{
			*destbis-- = *srcbis--;
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
