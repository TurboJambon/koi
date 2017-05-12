/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 14:47:59 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/12 14:54:09 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			typestat(struct stat stats)
{
	int	type;

	type = 0;
	if ((stats.st_mode & S_IFDIR) > 0)
		type = 4;
	else if ((stats.st_mode & S_IFREG) > 0)
		type = 3;
	else if ((stats.st_mode & S_IFCHR) > 0)
		type = 2;
	else if ((stats.st_mode & S_IFBLK) > 0)
		type = 6;
	else if ((stats.st_mode & S_IFIFO) > 0)
		type = 1;
	else if ((stats.st_mode & S_IFLNK) > 0)
		type = 10;
	else if ((stats.st_mode & S_IFSOCK) > 0)
		type = 12;
	return (type);
}

void	print_mode(mode_t n)
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
