/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:33:32 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/10 14:04:41 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*spips;

	spips = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		spips[i] = 0;
		i++;
	}
}
