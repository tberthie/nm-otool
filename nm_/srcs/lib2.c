/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:23:26 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/24 17:37:05 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

size_t				ft_atoi(const char *s)
{
	size_t			nbr;

	nbr = 0;
	while (*s <= '9' && *s >= '0')
		nbr = nbr * 10 + *s++ - '0';
	return (nbr);
}

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

void				ft_strpush(char **dst, char *str)
{
	char			*new;
	size_t			len;

	len = ft_strlen(*dst) + ft_strlen(str) + 1;
	if (!(new = malloc(len)))
		error_exit("Malloc failed.", 0);
	ft_memcpy(new, *dst, ft_strlen(*dst));
	ft_memcpy(new + ft_strlen(*dst), str, ft_strlen(str));
	new[len] = 0;
//	free(*dst);
	*dst = new;
}

void				*ft_memalloc(size_t size)
{
	void			*ptr;

	if (!(ptr = malloc(size)))
		error_exit("Malloc failed.", 0);
	while (size--)
		((char*)ptr)[size] = 0;
	return (ptr);
}
