/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 16:34:58 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/12 18:13:21 by dchirol          ###   ########.fr       */
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
		ft_putendl(av[i]);
		i++;
	}
}

int				ft_ls(char *s, t_uint prout)
{
	(void)s;
	(void)prout;
	return (1);
}

int				is_folder(char *name)
{
	return (name[0] == 'Z');
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
	int i;
	int flag;

	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (i < size)
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

void			sort_params(char **av, int ac)
{
	int i;
	int j;

	i = 0;
	j = ac - 1;

	while (i < ac && !is_folder(av[i]))
		i++;
	while (j >= 0 && is_folder(av[j]))
		j--;
	while (i < j)
	{
		if (is_folder(av[i]))
		{
			ft_swaptab(av + i, av + j);
			i++;
			j--;
		}
		else
			i++;
	}
	ft_affarg(av, ac);
	sort_str(av, j - 1);
	sort_str(av + j - 1, ac - j - 1);
	ft_putendl("---------");
	ft_affarg(av, ac);
}

void			ft_multi_ls(char **av, int ac, t_uint flags)
{
	int i;

	i = 0;
	while (i < ac)
	{
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
	sort_params(av, ac);
	ft_multi_ls(av, ac, flags);
	return (0);
}
