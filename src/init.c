/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 21:31:52 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/25 21:36:23 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				put_mystats(t_my_stats *stats, int ac)
{
	int i;

	i = 0;
	while (i < ac)
	{
		ft_putendl_buf(stats[i].name);
		i++;
	}

}

void				ft_fill_name(char **av, t_my_stats *my_stats, int *ac, t_uint flags)
{
	int i;
	int tmp;

	tmp = *ac;
	i = 0;
	while (i < tmp)
	{
		if (av[i])
		{
			my_stats[i].name = av[i];
			my_stats[i].path = av[i];
		}
		else
			(*ac)--;
		i++;		
	}
}

blkcnt_t			ft_stat(t_my_stats *my_stats, t_uint flags, int ac)
{	
	int 		i;
	blkcnt_t 	blocks;

	i = 0;
	blocks = 0;
	while (i < ac)
	{
		lstat(my_stats[i].path, &(my_stats[i].stat));
		i++;
	}
	i = 0;
	while (i < ac)
	{
		my_stats[i].uid = ft_strdup(getpwuid(my_stats[i].LS_UID)->pw_name);
		my_stats[i].gid = ft_strdup(getgrgid(my_stats[i].LS_GID)->gr_name);
		my_stats[i].rdev = my_stats[i].stat.st_rdev;
		my_stats[i].dev = my_stats[i].stat.st_dev;
		blocks += my_stats[i].stat.st_blocks;
		i++;
	}
	return (blocks);
}

t_stat			*fill_folder_infos(char **av, int ac)
{
	int 			i;
	t_stat 	*infos;

	if (!(infos = (t_stat*)malloc(sizeof(t_stat) * ac)))
		return (NULL);
	i = 0;
	while (i < ac)
	{
		lstat(av[i], &infos[i]);
		i++;
	}
	return (infos);
}