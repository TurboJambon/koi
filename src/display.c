/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 21:38:22 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/27 17:46:17 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_put_link(t_my_stats stats, t_uint flags)
{
	int		ret;
	char	buf[256];

	flags = 0;
	ft_putstr_buf(" -> ");
	ret = readlink(stats.path, buf, 256);
	buf[ret] = '\0';
	ft_putstr_buf(buf);
}

void		printtype(mode_t mode)
{
	static char			vtype[18] = "?pc?d?b?-?l??????";

	ft_putchar_buf(vtype[mode]);
}

void		ft_mode(mode_t n)
{
	static char		mode[9];

	mode[0] = '-' + ((n & 0400) > 0) * ('r' - '-');
	mode[1] = '-' + ((n & 0200) > 0) * ('w' - '-');
	mode[2] = '-' + ((n & 0100) > 0) * ('x' - '-');
	mode[3] = '-' + ((n & 0040) > 0) * ('r' - '-');
	mode[4] = '-' + ((n & 0020) > 0) * ('w' - '-');
	mode[5] = '-' + ((n & 0010) > 0) * ('x' - '-');
	mode[6] = '-' + ((n & 0004) > 0) * ('r' - '-');
	mode[7] = '-' + ((n & 0002) > 0) * ('w' - '-');
	mode[8] = '-' + ((n & 0001) > 0) * ('x' - '-');
	if (n & 04000)
		mode[2] = 'S' * (mode[2] == '-') + 's' * (mode[2] == 'x');
	if (n & 02000)
		mode[5] = 'S' * (mode[5] == '-') + 's' * (mode[5] == 'x');
	if (n & 01000)
		mode[8] = 'T' * (mode[8] == '-') + 't' * (mode[8] == 'x');
	ft_buf(1, mode, 9);
}

void		ft_putdate(time_t date)
{
	char	*str;

	str = ctime(&date);
	if (time(NULL) - date > 15768000)
	{
		ft_buf(1, str + 4, 6);
		ft_putchar_buf(' ');
		ft_buf(1, str + 20, 4);
		ft_putchar_buf(' ');
	}
	else
	{
		ft_buf(1, str + 4, 12);
	}
}

void		ft_put_name(t_my_stats stat, mode_t mode, t_uint flags)
{
	static char			*vtype[18] = {"", YEL, BLUY, "", CYN, "",
									BLUB, "", "", "",
									MAG, "", "", "", "", "", ""};

	if (OPTGM)
	{
		ft_putstr_buf(vtype[mode >> 12]);
		if (mode & S_IFREG && !(mode >> 12 == 10) && (mode & 0111))
			ft_putstr_buf(RED);
	}
	ft_putstr_buf(stat.name);
	if (OPTP && (mode & S_IFDIR))
		ft_putstr_buf("/");
	ft_putstr_buf(RESET);
}
