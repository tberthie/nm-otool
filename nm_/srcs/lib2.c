/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:23:26 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/20 21:49:38 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void				ft_memcpy(void *dst, const void *src, size_t len)
{
	while (len--)
		*(char*)dst++ = *(char*)src++;
}

char				*ft_strdup(const char *s1)
{
	char			*s2;

	if (!(s2 = malloc(ft_strlen(s1) + 1)))
		error_exit("Malloc failed.", 0);
	ft_memcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}

size_t				ft_readnbr(const char *s)
{
	size_t			size;

	size = 0;
	while (*s && *s >= 0 && *s <= 9)
		size = size * 10 + *s++;
	return (size);
}
