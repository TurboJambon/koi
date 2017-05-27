/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:13 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/27 16:51:55 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_av_to_stats(char **av, t_uint flags, int start)
{
	t_my_stats	*my_stats;

	my_stats = malloc(sizeof(*my_stats) * start);
	ft_fill_name(av, my_stats, &start, flags);
	ft_ls_file(my_stats, flags, start);
	ft_free_spe(my_stats, start);
	return (0);
}

void			param_sorter(char **av, char **avbis, int ac, t_uint flags)
{
	int			tmp;
	int			i;
	int			start;
	int			end;

	start = 0;
	i = 0;
	end = ac - 1;
	while (i < ac)
	{
		tmp = is_folder(av[i]);
		if (tmp == 0)
			avbis[start++] = av[i];
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
}

void			sort_params(char **av, int ac, t_uint flags)
{
	char		**avbis;

	if (!(avbis = (char **)malloc(sizeof(*avbis) * ac)))
		return ;
	param_sorter(av, avbis, ac, flags);
	free(avbis);
}

int				check_folder(char *name, t_uint flags)
{
	if (is_folder(name))
	{
		ft_ls_folder(&name, flags, 1);
		return (0);
	}
	ft_av_to_stats(&name, flags, 1);
	free(name);
	return (0);
}

int				main(int ac, char **av)
{
	t_uint			flags;
	static int		i = 1;
	char			**dot;

	flags = 0;
	if (ac < 2)
		return (ft_ls_folder(put_dot(), flags, ac));
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
