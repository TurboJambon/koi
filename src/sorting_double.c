/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 21:21:44 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 18:53:40 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort_str_ru(t_my_stats *stats, int size)
{
	int		flag;
	int		i;

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
	int		flag;
	int		i;

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
	int		flag;
	int		i;

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

void			sort_folder_ru(char **av, t_stat *infos, int size)
{
	int		flag;
	int		i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (infos[i].st_atime > infos[i + 1].st_atime)
			{
				ft_swapstat(infos + i, infos + i + 1);
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_folder_rt(char **av, t_stat *infos, int size)
{
	int		flag;
	int		i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (infos[i].st_mtime > infos[i + 1].st_mtime)
			{
				ft_swapstat(infos + i, infos + i + 1);
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}
