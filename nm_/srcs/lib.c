/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:11:34 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/24 17:33:36 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char				ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s2 - *s1);
}

char				ft_memcmp(char *d1, char *d2, size_t len)
{
	while (len--)
		if (*d1++ != *d2++)
			return (1);
	return (0);
}

size_t				ft_strlen(const char *str)
{
	const char		*beg;

	beg = str;
	while (*str)
		str++;
	return (str - beg);
}

void				ft_memset(char *dst, char c, size_t len)
{
	while (len--)
		*dst++ = c;
}

void				ft_arrpush_ascii(void ***dst, void *elem)
{
	int				len;
	void			**tab;
	void			**new;

	len = 0;
	tab = *dst;
	while (tab[len])
		len++;
	if (!(new = malloc(8 * (len + 2))))
		error_exit("Malloc failed.", 0);
	new[len + 1] = 0;
	len = 0;
	while (*tab && ft_strcmp(((t_symbol*)elem)->name,
				((t_symbol*)(*tab))->name) < 0)
		new[len++] = *tab++;
	new[len++] = elem;
	while (*tab)
		new[len++] = *tab++;
//	free(*dst);
	*dst = (void**)new;
}
