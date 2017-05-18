/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 18:37:16 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/18 19:56:13 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_dirlen(DIR *dir, int a, char *file)
{
	struct dirent	*read;
	int				i;

	i = 0;
	dir = opendir(file);
	while ((read = readdir(dir)))
	{
		if ((read->d_name[0] == '.' && a == 1)
			|| a == 1 || (a == 0 && read->d_name[0] != '.'))
			i++;
	}
	closedir(dir);
	return (i);
}

void			ft_affarg(char **av, int ac)
{	
	int i;

	i = 0;
	while (i < ac)
	{
		if (av[i])
			ft_putendl(av[i]);
		i++;
	}
}

void			ft_swapstat(t_stat *s1, t_stat *s2)
{
	t_stat tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void			ft_swapmystats(t_my_stats *s1, t_my_stats *s2)
{
	t_my_stats tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void			ft_swaptab(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int				is_folder(char *name)
{
	t_stat 		stats;

	if (lstat(name, &stats) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (S_ISDIR(stats.st_mode));
}
