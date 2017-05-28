/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 18:25:55 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 19:39:55 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_norme_screw(char **avbis, t_uint flags, int start, int ac)
{
	ft_av_to_stats(avbis, flags, start);
	ft_ls_folder(avbis + start, flags, ac - start);
}

void			main_ac_zero(t_uint flags)
{
	char			**dot;

	if (OPTD)
		ft_av_to_stats((dot = put_dot()), flags, 1);
	else
		ft_ls_folder((dot = put_dot()), flags, 1);
	free(dot[0]);
	free(dot);
}

void			ft_blanks_2(t_my_stats *stats, int *blanks, int i)
{
	int		tmp;

	tmp = ft_nblen(stats[i].LS_SIZE);
	if (tmp > blanks[3])
		blanks[3] = tmp;
	if ((stats[i].LS_MODE >> 12) == 2 || (stats[i].LS_MODE >> 12) == 6)
	{
		tmp = ft_nblen(stats[i].dev >> 24);
		if (tmp > blanks[4])
			blanks[4] = tmp;
		tmp = ft_nblen(stats[i].dev & 0xfff);
		if (tmp > blanks[5])
			blanks[5] = tmp;
	}
}

void			ft_blanks(t_my_stats *stats, int ac, int *blanks)
{
	int		i;
	int		tmp;

	ft_bzero(blanks, 24);
	i = 0;
	while (i < ac)
	{
		tmp = ft_nblen(stats[i].LS_NLINK);
		if (tmp > blanks[0])
			blanks[0] = tmp;
		tmp = ft_strlen(stats[i].uid);
		if (tmp > blanks[1])
			blanks[1] = tmp;
		tmp = ft_strlen(stats[i].gid);
		if (tmp > blanks[2])
			blanks[2] = tmp;
		ft_blanks_2(stats, blanks, i);
		i++;
	}
	if (blanks[4] + blanks[5] + 1 > blanks[3])
		blanks[3] = blanks[4] + 1 + blanks[5];
}
