/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 15:47:11 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 17:01:42 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_put_ls_file_l(t_my_stats *stats,
				int i, t_uint flags, int *blanks)
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

void			ft_put_ls_files(t_my_stats *stats, int ac,
				t_uint flags, blkcnt_t blocks)
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
			ft_put_ls_file_l(stats, i, flags, blanks);
		else
		{
			ft_put_name(stats[i], stats[i].LS_MODE, flags);
			ft_putchar_buf('\n');
		}
		i++;
	}
}
