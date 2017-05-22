/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:54 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/22 14:10:20 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			printacl(char *file)
{
	acl_t		acl;
	ssize_t		aclvalue;

	aclvalue = listxattr(file, NULL, 1, XATTR_NOFOLLOW);
	if (aclvalue > 0)
		ft_putchar_buf('@');
	else
	{
		acl = acl_get_file(file, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			ft_putchar_buf('+');
		else
			ft_putchar_buf(' ');
		acl_free((void*)acl);
	}
}

char	*ft_strjoin_ls(char *s1, char *s2)
{
	char	*ret;
	int		size1;
	int		size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(*ret) * (size1 + size2 + 2))))
		ft_putstr_buf("error malloc in ft_strjoin_ls");
	ft_memcpy(ret, s1, size1);
	ret[size1] = '/';
	ft_memcpy(ret + size1 + 1, s2, size2);
	ret[size1 + size2 + 1] = '\0';
	return (ret);
}

void			printtype(mode_t mode)
{
	static char			vtype[18] = "?pc?d?b?-?l??????";

	ft_putchar_buf(vtype[mode]);
}

void			put_mystats(t_my_stats *stats, int ac)
{
	int i;

	i = 0;
	while (i < ac)
	{
		ft_putendl_buf(stats[i].name);
		i++;
	}

}

void			ft_fill_name(char **av, t_my_stats *my_stats, int *ac, t_uint flags)
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

void			ft_stat(t_my_stats *my_stats, t_uint flags, int ac)
{
	int 	i;

	i = 0;
	while (i < ac)
	{
		lstat(my_stats[i].path, &(my_stats[i].stat));
		i++;
	}
	if (OPTL)
	{
		i = 0;
		while (i < ac)
		{
			my_stats[i].uid = ft_strdup(getpwuid(my_stats[i].LS_UID)->pw_name);
			my_stats[i].gid = ft_strdup(getgrgid(my_stats[i].LS_GID)->gr_name);
			my_stats[i].rdev = my_stats[i].stat.st_rdev;
			my_stats[i].dev = my_stats[i].stat.st_dev;
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
	ft_buf(1, mode, 9);
}

void			ft_put_name(t_my_stats stat, mode_t mode, t_uint flags)
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
	ft_putstr_buf(RESET);
}

void			ft_put_link(t_my_stats stats, t_uint flags)
{
	int		ret;
	char	buf[256];

	ft_put_name(stats, stats.LS_MODE, flags);
	ft_putstr_buf(" -> ");
	ret = readlink(stats.path, buf, 256);
	buf[ret] = '\0';
	ft_putendl_buf(buf);
}

void		ft_putdev(dev_t dev, dev_t rdev)
{
	ft_putnbr_buf(dev);
	ft_putchar_buf('\t');
	ft_putnbr_buf(rdev);
	ft_putchar_buf('\t');
}

void			ft_put_ls_files(t_my_stats *stats, int ac, t_uint flags)
{
	int i;

	i = 0;
	ft_buf(0, NULL, -1);
	ft_putendl_buf(stats[i].path);
	while (i < ac)
	{
		if (OPTL)
		{
			printtype((stats[i].LS_MODE >> 12));
			ft_mode(stats[i].LS_MODE);
			printacl(stats[i].name);
			ft_putchar_buf('\t');
			ft_putnbr_buf(stats[i].LS_NLINK);
			ft_putchar_buf('\t');
			ft_putstr_buf(stats[i].uid);
			ft_putchar_buf('\t');
			ft_putstr_buf(stats[i].gid);
			ft_putchar_buf('\t');
			((stats[i].LS_MODE >> 12) == 2 || (stats[i].LS_MODE >> 12) == 6) ? ft_putdev(stats[i].dev, stats[i].rdev): ft_putnbr_buf(stats[i].LS_SIZE);
			ft_putchar_buf('\t');
			if (OPTU)
				ft_buf(1, ctime(&stats[i].LS_ATIME) + 4, 12);
			else
				ft_buf(1, ctime(&stats[i].LS_MTIME) + 4, 12);
			ft_putchar_buf('\t');
			if ((stats[i].LS_MODE & S_IFLNK) == S_IFLNK)
				ft_put_link(stats[i], flags);
			else
			{
				ft_put_name(stats[i], stats[i].LS_MODE, flags);
				ft_putchar_buf('\n');
			}
		}
		else
		{
			ft_put_name(stats[i], stats[i].LS_MODE, flags);
			ft_putchar_buf('\t');
		}
		i++;
	}
}

t_stat	*fill_folder_infos(char **av, int ac)
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

void			ft_sorts_folder(char **av, t_stat *infos, int ac, t_uint flags)
{
	if (OPTT && OPTR)
		sort_folder_rt(av, infos, ac);
	else if (OPTU && OPTR)
		sort_folder_ru(av, infos, ac);
	else if (OPTT)
		sort_folder_t(av, infos, ac);
	else if (OPTU)
		sort_folder_u(av, infos, ac);
	else if (OPTR)
		sort_folder_r(av, ac);
	else if (OPTF)
		;
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

	i = 0;
	while (i < ac)
	{
		if (!(spoups = (t_my_stats*)malloc(sizeof(*spoups) * 10000)))
			return ;
		if (OPTRM)
			if (!(coucouille = (char**)malloc(sizeof(*coucouille) * 10000)))
				return ;
		while (!(dir = opendir(av[i])))
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
					coucouille[p] = spoups[w].path;
					p++;
				}
				w++;
			}
		}
		closedir(dir);
		ft_ls_file(spoups, flags, w);
		ft_putstr_buf("\n");
		if (OPTRM)
		{
			ft_ls_folder(coucouille, flags, p);
		}
		i++;
		free(spoups);
	}
}

int				ft_ls_folder(char **av, t_uint flags, int ac)
{
	t_stat 	*infos;

	infos = fill_folder_infos(av, ac);
	ft_sorts_folder(av, infos, ac, flags);
	ft_opendir(av, ac, flags);
	ft_buf(0, NULL, -1);
	return (1);
}

int				ft_ls_file(t_my_stats *my_stats, t_uint flags, int ac)
{
	if (OPTL || OPTT || OPTU)
		ft_stat(my_stats, flags, ac);
	ft_sorts(my_stats, ac, flags);
	ft_put_ls_files(my_stats, ac, flags);
	return (0);
}


/*FAIR D FRI DAN LE LS*/