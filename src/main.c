/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:13 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 19:45:27 by dchirol          ###   ########.fr       */
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
	static int	i = 0;
	static int	start = 0;
	int			end;

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
			{
				ft_forbidden(av[i]);
				avbis[end] = ft_strdup("\0");
			}
			end--;
		}
		i++;
	}
	ft_norme_screw(avbis, flags, start, ac);
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
	static t_uint	flags = 0;
	static int		i = 1;

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
		main_ac_zero(flags);
	else
		sort_params(av, ac, flags);
	ft_buf(0, NULL, -1);
	return (0);
}
