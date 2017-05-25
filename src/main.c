/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:13 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/25 17:10:58 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_free_spe(t_my_stats *stats, int ac)
{
	int i;

	i = 0;
	while (i < ac)
	{
		free(stats[i].gid);
		free(stats[i].uid);
		i++;
	}
	free(stats);
}

int				ft_av_to_stats(char **av, t_uint flags, int start)
{
	t_my_stats 	*my_stats;

	my_stats = malloc(sizeof(*my_stats) * start);
	ft_fill_name(av, my_stats, &start, flags);
	ft_ls_file(my_stats, flags, start);
	ft_free_spe(my_stats, start);
	return (0);
}

void			sort_params(char **av, int ac, t_uint flags)
{
	int		i;
	int		start;
	int		end;
	char	**avbis;
	int		tmp;

	if (!(avbis = (char **)malloc(sizeof(*avbis) * ac)))
		return ;
	start = 0;
	end = ac - 1;
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
	ft_av_to_stats(avbis, flags, start);
	ft_ls_folder(avbis + start, flags, ac - start);
	free(avbis);
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
	(*tab)['g'] = LSG;
	(*tab)['G'] = LSGM;
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
			ft_putstr_buf("illegal options");
			ft_buf(0, NULL, -1);
			exit(0);
		}
		av++;
	}
}

char			**put_dot()
{
	char **point;

	point = (char**)malloc(sizeof(char*) * 1);
	point[0] = ft_strdup(".");
	return (point);
}

int				check_folder(char *name, t_uint flags)
{
	if (is_folder(name))
	{
		ft_ls_folder(&name, flags, 1);
		ft_buf(0, NULL, -1);
		return (0);
	}
	ft_av_to_stats(&name, flags, 1);
	ft_buf(0, NULL, -1);
	free(name);
	return (0);
}

int 			main(int ac, char **av)
{
	t_uint	flags;
	int		i;
	char 	**dot;	
	char	*str;

	flags = 0;
	if (ac < 2)
		return(ft_ls_folder(put_dot(), flags, ac));
	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		get_flags(av[i] + 1, &flags);
		i++;
	}
	av += i;
	ac -= i;
	if (ac == 0)
	{
		ft_ls_folder((dot = put_dot()), flags, 1);
		free(dot[0]);
		free(dot);
	}
	else 
		sort_params(av, ac, flags);
	ft_buf(0, NULL, -1);
	return (0);
}
