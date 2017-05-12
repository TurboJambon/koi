/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:35:51 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:18:57 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	y;
	char			*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(str))
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		str[i] = (char)s1[i];
		i++;
	}
	y = 0;
	while (y < ft_strlen(s2))
	{
		str[i] = (char)s2[y];
		i++;
		y++;
	}
	str[i] = '\0';
	return (str);
}
