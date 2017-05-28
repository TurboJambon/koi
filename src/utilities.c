/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:37:16 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 17:29:19 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**put_dot(void)
{
	char **point;

	point = (char**)malloc(sizeof(char*) * 1);
	point[0] = ft_strdup(".");
	return (point);
}

void			ft_swapstat(t_stat *s1, t_stat *s2)
{
	t_stat tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void			ft_swapmystats(t_my_stats *s1, t_my_stats *s2)
{
	t_my_stats tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void			ft_swaptab(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int				is_folder(char *name)
{
	t_stat	stats;

	if (lstat(name, &stats) == -1)
		return (-1);
	return (S_ISDIR(stats.st_mode));
}
