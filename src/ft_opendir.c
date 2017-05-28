/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 15:47:15 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 16:12:40 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_realloc_av(t_opendir *opendir)
{
	char **tmp;

	opendir->maxp *= 10;
	tmp = (char**)malloc(sizeof(char*) * (opendir->maxp));
	ft_memmove(tmp, opendir->coucouille, (sizeof(char**) * opendir->maxp) / 10);
	free(opendir->coucouille);
	opendir->coucouille = tmp;
}

void			ft_realloc_mystats(t_opendir *opendir)
{
	t_my_stats *tmp;

	opendir->maxw *= 10;
	tmp = (t_my_stats*)malloc(sizeof(t_my_stats) * (opendir->maxw));
	ft_memmove(tmp, opendir->spoups, (sizeof(t_my_stats) * opendir->maxw) / 10);
	free(opendir->spoups);
	opendir->spoups = tmp;
}

void			ft_opendir_3(char **av, t_uint flags, int i, t_opendir *opendir)
{
	while ((opendir->dirent = readdir(opendir->dir)))
	{
		if (opendir->LS_NAME[0] == '.' && !OPTA)
			;
		else
		{
			opendir->spoups[opendir->w].path = ft_strcmp(av[i], ".") == 0 ?
			ft_strdup(opendir->LS_NAME) :
			ft_strjoin_ls(av[i], opendir->LS_NAME);
			opendir->spoups[opendir->w].name =
			ft_strdup(opendir->LS_NAME);
			if (OPTRM && opendir->LS_TYPE == DT_DIR &&
			*(t_uhint*)opendir->LS_NAME != 0x2e
			&& ((*(t_uint*)opendir->LS_NAME) & 0xffffff) != 0x2e2e)
			{
				opendir->coucouille[opendir->p] =
				ft_strdup(opendir->spoups[opendir->w].path);
				opendir->p++;
				if (opendir->p >= opendir->maxp)
					ft_realloc_av(opendir);
			}
			opendir->w++;
			if (opendir->w >= opendir->maxw)
				ft_realloc_mystats(opendir);
		}
	}
}

void			ft_opendir_2(char **av, t_uint flags, DIR *dir, int i)
{
	t_opendir opendir;

	opendir.maxp = 100;
	opendir.maxw = 100;
	opendir.p = 0;
	opendir.w = 0;
	opendir.spoups = NULL;
	if (!(opendir.spoups =
		(t_my_stats*)malloc(sizeof(*opendir.spoups) * 100)))
		return ;
	opendir.coucouille = NULL;
	if (OPTRM)
		if (!(opendir.coucouille =
			(char**)malloc(sizeof(*opendir.coucouille) * 100)))
			return ;
	opendir.dir = dir;
	ft_opendir_3(av, flags, i, &opendir);
	closedir(opendir.dir);
	ft_ls_file(opendir.spoups, flags, opendir.w);
	ft_free(opendir.spoups, opendir.w);
	if (OPTRM)
	{
		ft_ls_folder(opendir.coucouille, flags, opendir.p);
		ft_free_stat(opendir.coucouille, opendir.p);
	}
}

void			ft_opendir(char **av, int ac, t_uint flags)
{
	DIR			*dir;
	int			i;
	static int	flag = 0;

	i = 0;
	while (i < ac)
	{
		if (flag)
			ft_putstr_buf("\n");
		flag = 1;
		if (av[i][0] != '\0' && ft_strcmp(av[i], ".") != 0)
		{
			ft_putstr_buf(av[i]);
			ft_putendl_buf(":");
		}
		if ((dir = opendir(av[i])))
			ft_opendir_2(av, flags, dir, i);
		else
			ft_put_error(av[i]);
		i++;
	}
}
