/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_folder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:50:05 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/22 13:52:55 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort_folder_u(char **av, t_stat *infos, int size)
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
			if (infos[i].st_atime < infos[i + 1].st_atime)
			{
				ft_swapstat(infos + i, infos + i + 1);
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_folder_t(char **av, t_stat *infos, int size)
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
			if (infos[i].st_mtime < infos[i + 1].st_mtime)
			{
				ft_swapstat(infos + i, infos + i + 1);
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_folder_ru(char **av, t_stat *infos, int size)
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
	int 		flag;
	int 		i;

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

void			sort_folder(char **av, int size)
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
			if (ft_strcmp(av[i], av[i + 1]) > 0)
			{
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_folder_r(char **av, int size)
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
			if (ft_strcmp(av[i], av[i + 1]) < 0)
			{
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}