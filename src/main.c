/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:13 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/13 19:32:27 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "ft_ls.h"

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

void			ft_swaptab(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void			sort_str(char **av, int size)
{
	int flag;
	int i;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(av[i], av[i + 1]) > 0)
			{
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

char			**sort_params(char **av, int ac)
{
	int		i;
	int		start;
	int		end;
	char	**avbis;
	int		tmp;

	if (!(avbis = (char **)malloc(sizeof(*avbis) * (ac + 1))))
		return (NULL);
	start = 0;
	end = ac;
	i = 0;
	while (i < ac)
	{
		tmp = is_folder(av[i]);
		if (tmp == 0)
		{
			avbis[start] = av[i];
			start++;
		}
		else
		{
			if (tmp == 1)
				avbis[end] = av[i];
			else
				avbis[end] = ft_strdup("\0");
			end--;
		}
		i++;
	}
	avbis[start] = NULL;
	sort_str(avbis, start);
	sort_str(avbis + start + 1, ac - start);
	return (avbis);
}

void			ft_multi_ls(char **av, int ac, t_uint flags)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (av[i][0])
			ft_ls_file(av[i], flags);
		i++;
	}
	i++;
	while (i < ac)
	{
		if (av[i][0])
			ft_ls(av[i], flags);
		i++;
	}
}

void			fill_tab(t_uint **tab)
{
	*tab = (t_uint*)malloc(sizeof(**tab) * 127);
	ft_bzero(*tab, 127 * 4);
	(*tab)['l'] = LSL;
	(*tab)['a'] = LSA;
	(*tab)['r'] = LSR;
	(*tab)['t'] = LST;
	(*tab)['u'] = LSU;
	(*tab)['f'] = LSF;
	(*tab)['d'] = LSD;
	(*tab)['R'] = LSRM;
	(*tab)['G'] = LSG;
	(*tab)['p'] = LSP;
}

void		 	get_flags(char *av, t_uint *flags)
{
	static t_uint 	*tab = NULL;

	if (!tab)
		fill_tab(&tab);
	while (*av)
	{
		if (tab[(int)*av])
			*flags |= tab[(int)*av];
		else
		{
			ft_putstr("illegal options"); //A RAJOUTER DANS LIBFT
			exit(0);
		}
		av++;
	}
}



int 			main(int ac, char **av)
{
	t_uint	flags;
	int		i;

	flags = 0;
	if (ac < 2)
		return (ft_ls(ft_strdup("."), flags));
	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		get_flags(av[i] + 1, &flags);
		i++;
	}
	av += i;
	ac -= i;
	if (!ac)
		return(ft_ls(ft_strdup("."), flags));
	if (ac == 1)
		return(ft_ls(ft_strdup(*av), flags));
	av = sort_params(av, ac);
	ft_affarg(av, ac + 1);
	ft_multi_ls(av, ac + 1, flags);
	return (0);
}
