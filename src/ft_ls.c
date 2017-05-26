/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:54 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/26 12:21:13 by David            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_blanks(t_my_stats *stats, int ac, int *blanks)
{
	int		i;
	int		tmp;

	ft_bzero(blanks, 16);
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
		tmp = ft_nblen(stats[i].LS_SIZE);
		if (tmp > blanks[3])
			blanks[3] = tmp;
		i++;
	}
}


void			ft_sorts(t_my_stats *my_stats, int ac, t_uint flags)
{
	if (OPTT && OPTR)
		sort_str_rt(my_stats, ac);
	else if (OPTU && OPTR)
		sort_str_ru(my_stats, ac);
	else if (OPTU)
		sort_str_u(my_stats, ac);
	else if (OPTT)
		sort_str_t(my_stats, ac);
	else if (OPTR)
		sort_str_r(my_stats, ac);
	else if (OPTF)
		;
	else
		sort_str(my_stats, ac);
}



void			ft_put_ls_files(t_my_stats *stats, int ac, t_uint flags, blkcnt_t blocks)
{
	int		i;
	int		blanks[4];

	if (OPTL)
	{
		ft_blanks(stats, ac, blanks);
		ft_putstr_buf("total ");
		ft_putnbr_buf(blocks);
		ft_putchar_buf('\n');
	}
	i = 0;
	while (i < ac)
	{
		if (OPTL)
		{			
			printtype((stats[i].LS_MODE >> 12));
			ft_mode(stats[i].LS_MODE);
			printacl(stats[i].path);
			ft_putchar_buf(' ');
			ft_putnbrblanks_buf(stats[i].LS_NLINK, blanks[0]);
			ft_putchar_buf(' ');
			ft_putstrblanks_buf(stats[i].uid, blanks[1]);
			ft_putstr_buf("  ");
			ft_putstrblanks_buf(stats[i].gid, blanks[2]);
			ft_putstr_buf("  ");
			if ((stats[i].LS_MODE >> 12) == 2 || (stats[i].LS_MODE >> 12) == 6)
			 	ft_putdev(stats[i].rdev);
			else
				ft_putnbrblanks_buf(stats[i].LS_SIZE, blanks[3]);
			ft_putchar_buf(' ');
			if (OPTU)
				ft_putdate(stats[i].LS_ATIME);
			else
				ft_putdate(stats[i].LS_MTIME);
			ft_putchar_buf(' ');
			ft_put_name(stats[i], stats[i].LS_MODE, flags);
			if ((stats[i].LS_MODE & S_IFLNK) == S_IFLNK)
				ft_put_link(stats[i], flags);
			ft_putchar_buf('\n');
		}
		else
		{
			ft_put_name(stats[i], stats[i].LS_MODE, flags);
			ft_putchar_buf('\n');
		}
		i++;
	}
}

void			ft_sorts_folder(char **av, t_stat *infos, int ac, t_uint flags)
{
	if (OPTF)
		;
	else if (OPTU && OPTR && OPTT)
		sort_folder_ru(av, infos, ac);
	else if (OPTT && OPTR)
		sort_folder_rt(av, infos, ac);
	else if (OPTU && OPTT)
		sort_folder_u(av, infos, ac);
	else if (OPTT)
		sort_folder_t(av, infos, ac);
	else if (OPTR)
		sort_folder_r(av, ac);
	else
		sort_folder(av, ac);
}


void			ft_opendir(char **av, int ac, t_uint flags)
{
	DIR 		*dir;
	t_dirent	*dirent;
	t_my_stats 	*spoups;
	char 		**coucouille;
	int 		i;
	int			p;
	int			w;
	static int flag = 0;

	i = 0;
	while (i < ac)
	{
		if (flag)
			ft_putstr_buf("\n");
		flag = 1;
		if (av[i][0] != '.' && av[i][0] != '\0')
		{
			ft_putstr_buf(av[i]);
			ft_putendl_buf(":");
		}
		if ((dir = opendir(av[i])))
		{
			if (!(spoups = (t_my_stats*)malloc(sizeof(*spoups) * 5000)))
				return ;
			coucouille = NULL;
			if (OPTRM)
				if (!(coucouille = (char**)malloc(sizeof(*coucouille) * 5000)))
					return ;
			w = 0;
			p = 0; 
			while ((dirent = readdir(dir)))
			{
				if (LS_NAME[0] == '.' && !OPTA)
					;
				else
				{
					spoups[w].path = ft_strcmp(av[i], ".") == 0 ? ft_strdup(LS_NAME) : ft_strjoin_ls(av[i], LS_NAME);
					spoups[w].name = ft_strdup(LS_NAME);
					if (OPTRM && LS_TYPE == DT_DIR && *(t_uhint*)LS_NAME != 0x2e && ((*(t_uint*)LS_NAME) & 0xffffff) != 0x2e2e)
					{
						coucouille[p] = ft_strdup(spoups[w].path);
						p++;
					}
					w++;
				}
			}
			closedir(dir);
			ft_ls_file(spoups, flags, w);
			ft_free(spoups, w);
			if (OPTRM)
			{
				ft_ls_folder(coucouille, flags, p);
				ft_free_stat(coucouille, p);
			}
		}
		else
			ft_put_error(av[i]);
		i++;
	}
}

int				ft_ls_folder(char **av, t_uint flags, int ac)
{
	t_stat 	*infos;

	infos = fill_folder_infos(av, ac);
	ft_sorts_folder(av, infos, ac, flags);
	ft_opendir(av, ac, flags);
	ft_buf(0, NULL, -1);
	free(infos);

	return (1);
}

int				ft_ls_file(t_my_stats *my_stats, t_uint flags, int ac)
{
	blkcnt_t	blocks;

	if (OPTL || OPTT || OPTU || OPTGM)
		blocks = ft_stat(my_stats, flags, ac);
	ft_sorts(my_stats, ac, flags);
	ft_put_ls_files(my_stats, ac, flags, blocks);
	return (0);
}
