/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:13 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/19 18:00:46 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_av_to_stats(char **av, t_uint flags, int start)
{
	t_my_stats 	*my_stats;

	my_stats = malloc(sizeof(*my_stats) * start);
	ft_fill_name(av, my_stats, &start);
	ft_ls_file(my_stats, flags, start);
	return (0);
}

void			sort_params(char **av, int ac, t_uint flags)
{
	int		i;
	int		start;
	int		end;
	char	**avbis;
	int		tmp;

	if (!(avbis = (char **)malloc(sizeof(*avbis) * (ac + 1))))
		return ;
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

	ft_av_to_stats(avbis, flags, start);
	ft_ls_folder(avbis + start + 1, flags, ac - start);
	//sort_str(avbis, start);
	//sort_str(avbis + start + 1, ac - start);
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
			ft_putstr("illegal options"); //A RAJOUTER DANS LIBFT
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
	return(point);
}

int				check_folder(char *name, t_uint flags)
{
	if (is_folder(name))
		return (ft_ls_folder(&name, flags, 1));
	return (ft_av_to_stats(&name, flags, 1));

}

int 			main(int ac, char **av)
{
	t_uint	flags;
	int		i;

	flags = 0;
	if (ac < 2)
		return (ft_ls_folder(av, flags, ac));
	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0')
	{
		get_flags(av[i] + 1, &flags);
		i++;
	}
	av += i;
	ac -= i;
	if (ac == 0)
		return(ft_ls_folder(put_dot(), flags, 1));
	if (ac == 1)
		return(check_folder(ft_strdup(*av), flags));
	sort_params(av, ac, flags);
	return (0);
}
