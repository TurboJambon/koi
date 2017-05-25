/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writebuf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 16:56:55 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/25 20:54:49 by dchirol          ###   ########.fr       */
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

void	ft_putcharendl_buf_fd(char c, int fd)
{
	ft_buf(fd, &c, 1);
	ft_putchar_buf_fd('\n', fd);
}

void	ft_putnbr_buf(int n)
{
	if (n == -2147483648)
		ft_putstr_buf("-2147483648");
	else if (!(n > 2147483647 || n < -2147483648))
	{
		if (n < 0)
		{
			n = -n;
			ft_putchar_buf('-');
		}
		if (n >= 10)
		{
			ft_putnbr_buf(n / 10);
			ft_putnbr_buf(n % 10);
		}
		else
			ft_putchar_buf(n + '0');
	}
}

void	ft_putnbr_base_buf(int n, int base)
{
	if (n == -2147483648)
		ft_putstr_buf("-2147483648");
	else
	{
		if (n < 0)
		{
			n = -n;
			ft_putchar_buf('-');
		}
		if (n >= base)
		{
			ft_putnbr_base_buf(n / base, base);
			ft_putnbr_base_buf(n % base, base);
		}
		else
			ft_putchar_buf(n + '0');
	}
}

void	ft_putendl_buf_fd(char *str, int fd)
{
	size_t len;

if (!str)
		return ;
	len = ft_strlen(str);
	ft_buf(fd, str, len);
	ft_buf(fd, "\n", 1);
}

static int	ft_if(int fd, int size, t_uchar **buf, int *p)
{
	if (!*buf)
	{
		if (!(*buf = (t_uchar *)malloc(sizeof(**buf) * 100000)))
			ft_putendl_buf("error malloc in ft_buf");
	}
	if (size == -1)
	{
		write(fd, *buf, *p);
		*p = 0;
		return (0);
	}
	if (*p + size > 100000)
	{
		write(fd, *buf, *p);
		*p = 0;
	}
	return (1);
}

static void	ft_bufcpy(t_uchar *buf, int *p, void *str, int size)
{
	t_ulint	*tmp1;
	t_ulint	*tmp2;
	t_uchar	*tmp3;
	int		i;

	tmp1 = (t_ulint *)buf;
	tmp2 = (t_ulint *)str;
	tmp3 = (t_uchar *)str;
	i = 0;
	while (size >= 8)
	{
		tmp1[i] = tmp2[i];
		i++;
		size -= 8;
		*p += 8;
	}
	i *= 8;
	while (size > 0)
	{
		buf[i] = tmp3[i];
		i++;
		size--;
		(*p)++;
	}
}

int			ft_buf(int fd, void *str, int size)
{
	static t_uchar	*buf = NULL;
	static int		p = 0;

	if (!ft_if(fd, size, &buf, &p))
		return (p);
	if (size > 100000)
	{
		write(fd, str, size);
		return (size);
	}
	ft_bufcpy(buf + p, &p, str, size);
	return (0);
}
