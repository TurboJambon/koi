/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:38:23 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:25:07 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*mem;

	if (!(mem = (char *)malloc(size + 1)))
		return (NULL);
	ft_bzero((void *)mem, sizeof(char) * size + 1);
	return ((char *)mem);
}
