/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:13 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/14 17:28:48 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort_str_t(char **av, int size)
{	
	int 		flag;
	int 		i;
	t_stat 		stats1;
	t_stat 		stats2;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size - 1)
		{
			lstat(av[i], &stats1);
			lstat(av[i + 1], &stats2);
			if (stats1.st_mtime < stats2.st_mtime)
			{
				ft_swaptab(av + i, av + i + 1);
				flag = 1;
			}
			i++;
		}
	}
}

void			sort_str_r(char **av, int size)
{	
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < (size - 1) / 2)
	{
		ft_swaptab(av + i, av + size - 1 - i);
		i++;
	}
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

char			**sort_params(char **av, int ac, t_uint flags)
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
	tmp = -1;
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
	
	if (!OPTU)
	{
		sort_str(avbis, start);
		sort_str(avbis + start + 1, ac - start);
	}
	if (OPTT)
	{
		sort_str_t(avbis, start);
		sort_str_t(avbis + start + 1, ac - start);
	}
	if (OPTR)
	{
		sort_str_r(avbis, start);
		sort_str_r(avbis + start + 1, ac - start);
	}
	return (avbis);
}

void			ft_multi_ls(char **av, int ac, t_uint flags)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (av[i][0])
			ft_ls_file(av[i], flags, ac);
		i++;
	}
	i++;
	while (i < ac)
	{
		if (av[i][0])
			ft_ls(av[i], flags, ac);
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
		return (ft_ls(ft_strdup("."), flags, ac));
	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		get_flags(av[i] + 1, &flags);
		i++;
	}
	av += i;
	ac -= i;
	if (ac == 0)
		return(ft_ls(ft_strdup("."), flags, ac));
	if (ac == 1)
		return(ft_ls(ft_strdup(*av), flags, ac));
	av = sort_params(av, ac, flags);
	//ft_affarg(av, ac + 1);
	ft_multi_ls(av, ac + 1, flags);
	return (0);
}
