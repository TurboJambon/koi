/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:54 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 19:15:50 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_forbidden(char *str)
{
	ft_putstr_buf_fd("ls: ", 2);
	ft_putstr_buf_fd(str, 2);
	ft_putendl_buf_fd(": No such file or directory", 2);
}

void			ft_sorts(t_my_stats *my_stats, int ac, t_uint flags)
{
	if (OPTF)
		return ;
	else if (OPTU && OPTR && OPTT)
		sort_str_ru(my_stats, ac);
	else if (OPTT && OPTR)
		sort_str_rt(my_stats, ac);
	else if (OPTT)
		sort_str_t(my_stats, ac);
	else if (OPTR)
		sort_str_r(my_stats, ac);
	else
		sort_str(my_stats, ac);
}

void			ft_sorts_folder(char **av, t_stat *infos, int ac, t_uint flags)
{
	if (OPTF)
		return ;
	else if (OPTU && OPTR && OPTT)
		sort_folder_ru(av, infos, ac);
	else if (OPTT && OPTR)
		sort_folder_rt(av, infos, ac);
	else if (OPTU && OPTT)
		sort_folder_u(av, infos, ac);
	else if (OPTT)
		sort_folder_t(av, infos, ac);
	else if (OPTR)
		sort_folder_r(av, ac);
	else
		sort_folder(av, ac);
}

int				ft_ls_folder(char **av, t_uint flags, int ac)
{
	t_stat	*infos;

	infos = fill_folder_infos(av, ac);
	if (!OPTF)
		ft_sorts_folder(av, infos, ac, flags);
	ft_opendir(av, ac, flags);
	ft_buf(0, NULL, -1);
	free(infos);
	return (1);
}

int				ft_ls_file(t_my_stats *my_stats, t_uint flags, int ac)
{
	blkcnt_t	blocks;

	blocks = 0;
	if (OPTL || OPTT || OPTU || OPTGM)
		blocks = ft_stat(my_stats, flags, ac);
	if (!OPTF)
		ft_sorts(my_stats, ac, flags);
	ft_put_ls_files(my_stats, ac, flags, blocks);
	return (0);
}
