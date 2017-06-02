/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 19:37:50 by tberthie          #+#    #+#             */
/*   Updated: 2017/06/02 13:15:06 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "libft.h"

char			*get_symbol(t_symbol *sym, t_section **sections, char cap)
{
	unsigned long	off;

	off = sym->value;
	while (*(sections + 1) && (*sections)->off < off)
		sections++;
	if ((*sections)->id == TEXT)
		return (cap ? "T" : "t");
	else if ((*sections)->id == DATA)
		return (cap ? "D" : "d");
	else if ((*sections)->id == COMMON)
		return (cap ? "C" : "c");
	else if ((*sections)->id == BSS)
		return (cap ? "B" : "b");
	return (cap ? "S" : "s");
}

void			add_section_32(t_section ***sections, t_seg *seg)
{
	t_section	*section;

	section = ft_m(sizeof(t_section));
	if (!ft_strcmp(seg->segname, "__TEXT") ||
	!ft_strcmp(seg->segname, "__text"))
		section->id = TEXT;
	else if (!ft_strcmp(seg->segname, "__DATA") ||
	!ft_strcmp(seg->segname, "__data"))
		section->id = DATA;
	else if (!ft_strcmp(seg->segname, "__bss"))
		section->id = BSS;
	else if (!ft_strcmp(seg->segname, "__common"))
		section->id = COMMON;
	else
		section->id = OTHER;
	section->off = seg->fileoff;
	ft_parrpush((void***)sections, section);
}
