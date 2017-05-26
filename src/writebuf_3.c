/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writebuf_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 11:26:07 by David             #+#    #+#             */
/*   Updated: 2017/05/26 11:28:55 by David            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
