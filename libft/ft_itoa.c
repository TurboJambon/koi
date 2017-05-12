/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:45:23 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:13:51 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strconstruct(char *str, long n, int div)
{
	int i;

	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		i = 1;
		n = n * -1;
	}
	while (div >= 1)
	{
		str[i] = (n / div) + '0';
		n = n % div;
		div = div / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_itoa(int n)
{
	int		lenght;
	long	tmp;
	int		div;
	char	*str;

	tmp = (long)n;
	if (tmp < 0)
		tmp = tmp * -1;
	lenght = 1;
	div = 1;
	while (tmp > 9)
	{
		tmp = tmp / 10;
		lenght++;
		div = div * 10;
	}
	if (n < 0)
		lenght++;
	tmp = (long)n;
	if (!(str = (char*)malloc(sizeof(char) * (lenght + 1))))
		return (NULL);
	return (ft_strconstruct(str, tmp, div));
}
