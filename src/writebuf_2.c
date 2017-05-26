/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writebuf_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:22:25 by David             #+#    #+#             */
/*   Updated: 2017/05/26 11:26:02 by David            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putstr_buf(char *str)
{
	size_t len;

	if (!str)
		return ;
	len = ft_strlen(str);
	ft_buf(1, str, len);
}

void	ft_putendl_buf(char *str)
{
	size_t len;

if (!str)
		return ;
	len = ft_strlen(str);
	ft_buf(1, str, len);
	ft_buf(1, "\n", 1);
}

void	ft_putstr_buf_fd(char *str, int fd)
{
	size_t len;

if (!str)
		return ;
	len = ft_strlen(str);
	ft_buf(fd, str, len);
}

void	ft_putchar_buf(char c)
{
	ft_buf(1, &c, 1);
}

void	ft_putchar_buf_fd(char c, int fd)
{
	ft_buf(fd, &c, 1);
}
