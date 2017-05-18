/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:54 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/18 18:39:48 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			printacl(char *file)
{
	acl_t		acl;
	ssize_t		aclvalue;

	aclvalue = listxattr(file, NULL, 1, XATTR_NOFOLLOW);
	if (aclvalue > 0)
		ft_putchar('@');
	else
	{
		acl = acl_get_file(file, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			ft_putchar('+');
		else
			ft_putchar(' ');
		acl_free((void*)acl);
	}
}

void			printtype(int type)
{
	static char			vtype[13] = "?fc-d-b---l-s";

	ft_putchar(vtype[type]);
}

void			put_mystats(t_my_stats *stats, int ac)
{
	int i;

	i = 0;
	while (i < ac)
	{
		ft_putendl(stats[i].name);
		i++;
	}

}

void			ft_fill_name(char **av, t_my_stats *my_stats, int *ac)
{
	int i;
	int tmp;

	tmp = *ac;
	i = 0;
	while (i < tmp)
	{
		if (av[i])
			my_stats[i].name = av[i];
		else
			(*ac)--;
		i++;		
	}
}

void			ft_stat(t_my_stats *my_stats, char **av, t_uint flags, int ac)
{
	int 	i;

	i = 0;
	while (i < ac)
	{
		lstat(av[i], &(my_stats[i].stat));
		i++;
	}
	if (OPTL)
	{
		i = 0;
		while (i < ac)
		{
			my_stats[i].uid = ft_strdup(getpwuid(my_stats[i].LS_UID)->pw_name);
			my_stats[i].gid = ft_strdup(getgrgid(my_stats[i].LS_GID)->gr_name);
			i++;
		}
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

void	ft_mode(mode_t n)
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
	write(1, mode, 9);
}

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

void			ft_put_ls_files(t_my_stats *stats, int ac, t_uint flags)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (OPTL)
		{
			printtype(typestat(stats[i].stat));
			ft_mode(stats[i].LS_MODE);
			printacl(stats[i].name);
			ft_putchar('\t');
			ft_putnbr(stats[i].LS_NLINK);
			ft_putchar('\t');
			ft_putstr(stats[i].uid);
			ft_putchar('\t');
			ft_putstr(stats[i].gid);
			ft_putchar('\t');
			ft_putnbr(stats[i].LS_SIZE);
			ft_putchar('\t');
			if (OPTU)
				write(1, ctime(&stats[i].LS_ATIME) + 4, 12);
			else
				write(1, ctime(&stats[i].LS_MTIME) + 4, 12);
			write(1, "\t", 1);
			ft_putendl(stats[i].name);
		}
		else
		{
			ft_putstr(stats[i].name);
			ft_putchar('\t');
		}
		i++;
	}
}

int				ft_ls_folder(char **av, t_uint flags, int ac)
{
	return (1);
}

int				ft_ls_file(char **av, t_uint flags, int ac)
{
	t_my_stats 	*my_stats;

	my_stats = malloc(sizeof(*my_stats) * ac);
	ft_fill_name(av, my_stats, &ac);
	if (OPTL || OPTT || OPTU)
		ft_stat(my_stats, av, flags, ac);
	ft_sorts(my_stats, ac, flags);
	ft_put_ls_files(my_stats, ac, flags);
	//put_mystats(my_stats, ac);
	return (0);
}


/*FAIR D FRI DAN LE LS*/