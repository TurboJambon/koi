/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:45:10 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/07 15:35:45 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		y;
	char	*cpy;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	y = ft_strlen(s) - 1;
	while (s[y] == ' ' || s[y] == '\t' || s[y] == '\n')
		y--;
	cpy = ft_strsub(s, i, y - i + 1);
	if (cpy == NULL)
	{
		if (!(cpy = (char *)malloc(1)))
			return (NULL);
		cpy[0] = '\0';
	}
	return (cpy);
}
