/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 20:15:25 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 17:03:28 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

size_t			ft_strlen(const char *str)
{
	const char	*beg;

	beg = str;
	while (*str)
		str++;
	return (str - beg);
}

void			*ft_memalloc(size_t bytes)
{
	void		*ptr;

	if (!(ptr = malloc(bytes)))
		exit(1);
	return (ptr);
}

void			ft_parrpush(void ***tab, void *elem)
{
	void		**new;
	size_t		i;

	i = 0;
	while ((*tab)[i])
		i++;
	new = malloc(sizeof(void*) * (i + 2));
	new[i + 1] = 0;
	new[i] = elem;
	while (i--)
		new[i] = (*tab)[i];
	free(*tab);
	*tab = new;
}

char			*ft_strdup(const char *str)
{
	char		*new;

	new = ft_memalloc(ft_strlen(str) + 1);
	ft_memcpy(new, str, ft_strlen(str) + 1);
	return (new);
}

void			ft_memcpy(void *dst, const void *src, size_t len)
{
	while (len--)
		*(char*)dst++ = *(char*)src++;
}
