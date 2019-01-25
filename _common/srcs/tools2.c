/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:33:55 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 16:44:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

size_t				ft_atoi(const char *str)
{
	size_t			nbr;

	nbr = 0;
	while (*str && *str >= '0' && *str <= '9')
		nbr = nbr * 10 + *str++ - '0';
	return (nbr);
}

int					ft_memcmp(void *d1, void *d2, size_t len)
{
	char			*s1;
	char			*s2;

	s1 = d1;
	s2 = d2;
	while (--len && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s2 - *s1);
}

int					ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s2 - *s1);
}

void				ft_memset(void *dst, char c, size_t len)
{
	while (len--)
		*(char*)dst++ = c;
}
