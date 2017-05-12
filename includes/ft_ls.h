/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 14:58:24 by dchirol           #+#    #+#             */
/*   Updated: 2017/05/12 15:14:59 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# include <dirent.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>

# define OPTIONS "Rafglprtu"

//COLORS
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[1;96m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

//TYPEDEF
typedef unsigned long int		t_ulint;
typedef unsigned char			t_uchar;

//BUF FUNCTIONS
int								ft_buf(int fd, void *str, int size);

void							ft_putchar_buf(char c);
void							ft_putchar_buf_fd(char c, int fd);
void							ft_putcharendl_buf_fd(char c, int fd);

void							ft_putstr_buf(char *str);
void							ft_putstr_buf_fd(char *str, int fd);
void							ft_putendl_buf_fd(char *str, int fd);

void							ft_putnbr_buf(int n);

//STATS FUNCTIONS
void							print_mode(mode_t n);
int								typestat(struct stat stats);

#endif
