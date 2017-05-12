/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 14:44:57 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/12 14:50:38 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		freedir(t_dir *tab)
{
	int i;

	i = 0;
	while (tab[i].type)
	{
		ft_strdel(&tab[i].name);
		i++;
	}
}

char		*ft_strjoinchar(char const *s1, char const *s2, char c)
{
	size_t	i;
	int		j;
	char	*new;
	size_t	size;

	if (!s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	new = ft_strnew(size + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && i < size)
		new[j++] = s1[i++];
	i = 0;
	new[j++] = c;
	while (s2[i] && i < size)
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}