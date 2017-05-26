/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <dchirol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:35:33 by niragne           #+#    #+#             */
/*   Updated: 2017/05/26 21:37:04 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFF_SIZE 32

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_point
{
	int					x;
	int					y;
	int					z;
}				t_point;

typedef struct	s_vector
{
	int					x;
	int					y;
	int					z;
}				t_vector;

typedef struct	s_gnl
{
	char				*tmp;
	int					rd;
	char				buf[BUFF_SIZE + 1];
}				t_gnl;

int				get_next_line(const int fd, char **line);
void			ft_putchar(char c);
size_t			ft_strlen(char const *s);
void			ft_putstr(char const *s);
int				ft_strcmp(char *s1, char *s2);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memalloc(size_t size);
void			ft_putendl(char const *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_bzero(void	*s, size_t n);
char			*ft_strnew(size_t size);
int				ft_isascii(int c);
int				ft_isdigit(int c);
void			ft_putnbr(int n);
int				ft_isprint(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_memdel(void **ap);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
int				ft_isblanks(int c);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
int				ft_isspace(int c);
int				ft_atoi(const char *str);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
char			*ft_itoa(int n);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *s1, const char *s2, size_t n);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
t_point			ft_newpoint(int x, int y, int z);
t_point			ft_get_middle(t_point a, t_point b);
void			ft_lstdel(t_list **alst, void(*del)(void*, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_vector		*ft_newvector(int x, int y, int z);
t_point			ft_translation(t_point p, t_vector v);
int				ft_iscollinear(t_vector *v, t_vector *w);
t_vector		*ft_getvector(t_point *a, t_point *b);
int				ft_isupper(int c);
int				ft_islower(int c);
void			ft_lstadd(t_list **alst, t_list *new);
int				*ft_range(int min, int max);
size_t			ft_tablen(char **tab);
char			**ft_sort_tab(char **tab);
void			ft_putarr(char **tab);
void			ft_freear(char **tab);
int				ft_sqrt(int nb);
char			*ft_strtoupper(char *str);
char			*ft_strtolower(char *str);
void			ft_swap(int *a, int *b);
void			ft_foreach(int *tab, int length, void (*f)(int));
char			*ft_rot(char *str, int r);
void			*ft_realloc(void *ptr, size_t size);
char			*fd_to_str(int fd);
char			*ft_strndup(char const *s1, int n);
char			*ft_strrnchr(const char *s, int c, int n);
int				ft_swaparr(char **tab, int i);

#endif
