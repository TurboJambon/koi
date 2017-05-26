/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 21:29:04 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/26 11:26:02 by David            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_nblen(int nb)
{
	int		size;

	size = 1;
	while (nb >= 10)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

char			*ft_strjoin_ls(char *s1, char *s2)
{
	char	*ret;
	int		size1;
	int		size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(*ret) * (size1 + size2 + 2))))
		ft_putstr_buf("error malloc in ft_strjoin_ls");
	ft_memcpy(ret, s1, size1);
	ret[size1] = '/';
	ft_memcpy(ret + size1 + 1, s2, size2);
	ret[size1 + size2 + 1] = '\0';
	return (ret);
}

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

void	ft_free(t_my_stats *stats, int ac)
{
	int i;

	i = 0;

	while (i < ac)
	{
		free(stats[i].name);
		free(stats[i].path);
		free(stats[i].gid);
		free(stats[i].uid);
		i++;
	}
	free(stats);
}

void	ft_free_stat(char **av, int ac)
{
	int i;

	i = 0;
	while (i < ac)
	{
		free(av[i]);
		i++;
	}
	free(av);
}
