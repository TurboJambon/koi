/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:54 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/18 20:44:01 by dchirol          ###   ########.fr       */
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

char	*ft_strjoin_ls(char *s1, char *s2)
{
	char	*ret;
	int		size1;
	int		size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(*ret) * (size1 + size2 + 2))))
		ft_putstr("error malloc in ft_strjoin_ls");
	ft_memcpy(ret, s1, size1);
	ret[size1] = '/';
	ft_memcpy(ret + size1 + 1, s2, size2);
	ret[size1 + size2 + 1] = '\0';
	return (ret);
}

void			printtype(mode_t mode)
{
	static char			vtype[18] = "??c?d?b?-?l??????";

	ft_putchar(vtype[mode]);
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
			printtype((stats[i].LS_MODE >> 12));
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
	ft_affarg(av, ac);
}

void			ft_opendir(char **av, int ac, t_uint flags)
{
	DIR 		*dir;
	t_dirent	*dirent;
	char 		**spoups;
	char		**coucouille;
	int 		i;
	int			p;
	int			w;

	i = 0;
	p = 0;
	while (i < ac)
	{
		if (!(spoups = (char **)malloc(sizeof(char*) * 1000)))
			return ;
		if (!(coucouille = (char **)malloc(sizeof(char*) * 1000)))
			return ;
		dir = opendir(av[i]);
		w = 0;
		while ((dirent = readdir(dir)))
		{
			spoups[w] = ft_strcmp(av[i], ".") == 0 ? ft_strdup(LS_NAME) : ft_strjoin_ls(av[i], LS_NAME);
			if (LS_TYPE == DT_DIR)
			{
				coucouille[p] = spoups[w];
				p++;
			}
			w++;
		}
		ft_ls_file(spoups, flags, w);
		i++;
	}
}

int				ft_ls_folder(char **av, t_uint flags, int ac)
{
	t_stat 	*infos;

	infos = fill_folder_infos(av, ac);
	ft_sorts_folder(av, infos, ac, flags);
	ft_opendir(av, ac, flags);
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