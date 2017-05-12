/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchirol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:05:08 by dchirol           #+#    #+#             */
/*   Updated: 2016/11/12 12:14:38 by dchirol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, const char *s2)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	result = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (result);
}
