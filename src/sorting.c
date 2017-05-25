/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:50:05 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/25 16:27:14 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort_str_u(t_my_stats *stats, int size)
{	
	int 		flag;
	int 		i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (stats[i].LS_ATIME < stats[i + 1].LS_ATIME)
			{
				ft_swapmystats(stats + i, stats + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_str_t(t_my_stats *stats, int size)
{	
	int 		flag;
	int 		i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (stats[i].LS_MTIME < stats[i + 1].LS_MTIME)
			{
				ft_swapmystats(stats + i, stats + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_str(t_my_stats *stats, int size)
{
	int flag;
	int i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(stats[i].name, stats[i + 1].name) > 0)
			{
				ft_swapmystats(stats + i, stats + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_str_ru(t_my_stats *stats, int size)
{	
	int 		flag;
	int 		i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (stats[i].LS_ATIME > stats[i + 1].LS_ATIME)
			{
				ft_swapmystats(stats + i, stats + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_str_rt(t_my_stats *stats, int size)
{	
	int 		flag;
	int 		i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (stats[i].LS_MTIME > stats[i + 1].LS_MTIME)
			{
				ft_swapmystats(stats + i, stats + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_str_r(t_my_stats *stats, int size)
{
	int flag;
	int i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(stats[i].name, stats[i + 1].name) < 0)
			{
				ft_swapmystats(stats + i, stats + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}
