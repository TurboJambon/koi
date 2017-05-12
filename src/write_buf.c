/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 14:50:59 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/12 14:54:36 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putstr_buf(char *str)
{
	size_t len;

	len = ft_strlen(str);
	ft_buf(1, str, len);
}

void	ft_putstr_buf_fd(char *str, int fd)
{
	size_t len;

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

void	ft_putcharendl_buf_fd(char c, int fd)
{
	ft_buf(fd, &c, 1);
	ft_putchar_buf_fd('\n', fd);
}
