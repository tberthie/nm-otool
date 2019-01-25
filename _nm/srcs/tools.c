/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:37:39 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 17:03:13 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void				ft_parrpush_syms(t_sym ***addr, t_sym *elem)
{
	t_sym			**new;
	t_sym			**tab;
	size_t			len;

	tab = *addr;
	len = 0;
	while (tab[len])
		len++;
	new = ft_memalloc(sizeof(void*) * (len + 2));
	new[len + 1] = 0;
	len = 0;
	while (*tab && ft_strcmp((*tab)->name, elem->name) >= 0)
		new[len++] = *tab++;
	new[len++] = elem;
	while (*tab)
		new[len++] = *tab++;
	free(*addr);
	*addr = new;
}
