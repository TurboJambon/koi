/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: David <David@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:06:46 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:23:25 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cnt_words(const char *s, char c)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if (in_substring == 1 && *s == c)
			in_substring = 0;
		if (in_substring == 0 && *s != c)
		{
			in_substring = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int		ft_wordlen(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		nb_word;
	int		i;

	if (!(s))
		return (NULL);
	i = 0;
	nb_word = ft_cnt_words((const char *)s, c);
	if (!(str = (char **)malloc(sizeof(*str) * (nb_word + 1))))
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		str[i] = ft_strsub((const char *)s, 0, ft_wordlen((const char *)s, c));
		if (str[i] == NULL)
			return (NULL);
		s = s + ft_wordlen(s, c);
		i++;
	}
	str[i] = NULL;
	return (str);
}
