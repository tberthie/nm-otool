/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:09:02 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/09 02:37:34 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#include "libft.h"

#include <mach-o/nlist.h>

static void		dump(void *addr, unsigned char *data, unsigned int size)
{
	unsigned int	off;

	off = 16;
	ft_printf("%08x\t", (unsigned int)addr);
	while (size--)
	{
		hex_dump((unsigned char)*data++);
		off--;
		if (!off)
		{
			off = 16;
			ft_print(1, "\n");
			ft_printf("%08x\t", (unsigned int)(addr += 16));
		}
	}
	if (off != 16)
		ft_print(1, "\n");
}

static void		find_section(char *path, t_segment *seg, void *origin)
{
	unsigned int	size;
	t_section		*sec;

	ft_print(1, "%s:\nContents of (__TEXT,__text) section\n", path);
	sec = (void*)seg + sizeof(t_segment);
	size = seg->nsects;
	while (ft_strcmp(sec->sectname, "__text") && size--)
		sec += sizeof(t_section);
	if (size)
		dump((void*)(unsigned long)sec->addr, origin + sec->offset,
		(unsigned int)sec->size);
}

void			parse_32(char *path, void *data, void *origin,
				unsigned int size)
{
	t_segment		*load;

	while (size--)
	{
		load = (t_segment*)data;
		if (load->cmd == LC_SEGMENT && !ft_strcmp(load->segname, "__TEXT"))
			find_section(path, load, origin);
		data += load->cmdsize;
	}
}
