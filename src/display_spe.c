/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_spe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 21:26:26 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/28 17:04:36 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_putdev(dev_t rdev)
{
	ft_putnbr_buf(rdev >> 24);
	ft_putstr_buf(", ");
	ft_putnbr_buf(rdev & 0xfff);
	ft_putchar_buf('\t');
}

void		ft_putstrblanks_buf(char *str, int blanks)
{
	int		size;
	char	space[blanks];

	size = ft_strlen(str);
	ft_memset(space, ' ', blanks - size);
	ft_buf(1, space, blanks - size);
	ft_buf(1, str, size);
}

void		ft_putnbrblanks_buf(int nbr, int blanks)
{
	int		size;
	char	space[blanks];

	size = ft_nblen(nbr);
	ft_memset(space, ' ', blanks - size);
	ft_buf(1, space, blanks - size);
	ft_putnbr_buf(nbr);
}

void		printacl(char *file)
{
	acl_t		acl;
	ssize_t		aclvalue;

	aclvalue = listxattr(file, NULL, 1, XATTR_NOFOLLOW);
	if (aclvalue > 0)
		ft_putchar_buf('@');
	else
	{
		acl = acl_get_file(file, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			ft_putchar_buf('+');
		else
			ft_putchar_buf(' ');
		acl_free((void*)acl);
	}
}

void		ft_put_error(char *str)
{
	if (errno == 13)
	{
		ft_putstr_buf_fd("ls: ", 2);
		ft_putstr_buf_fd(str, 2);
		ft_putendl_buf_fd(": Permission denied", 2);
	}
}
