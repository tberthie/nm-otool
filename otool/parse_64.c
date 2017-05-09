/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:08:54 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/09 02:35:20 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#include "libft.h"

#include <mach-o/nlist.h>

static void		dump(void *addr, unsigned char *data, unsigned int size)
{
	unsigned int	off;

	off = 16;
	ft_printf("%016x\t", (unsigned int)addr);
	while (size--)
	{
		hex_dump((unsigned char)*data++);
		off--;
		if (!off)
		{
			off = 16;
			ft_print(1, "\n");
			ft_printf("%016x\t", (unsigned int)(addr += 16));
		}
	}
	if (off != 16)
		ft_print(1, "\n");
}

static void		find_section(char *path, t_segment_64 *seg, void *origin)
{
	unsigned int	size;
	t_section_64	*sec;

	ft_print(1, "%s:\nContents of (__TEXT,__text) section\n", path);
	sec = (void*)seg + sizeof(t_segment_64);
	size = seg->nsects;
	while (ft_strcmp(sec->sectname, "__text") && size--)
		sec += sizeof(t_section_64);
	if (size)
		dump((void*)sec->addr, origin + sec->offset, (unsigned int)sec->size);
}

void			parse_64(char *path, void *data, void *origin,
				unsigned int size)
{
	t_segment_64		*load;

	while (size--)
	{
		load = (t_segment_64*)data;
		if (load->cmd == LC_SEGMENT_64 && !ft_strcmp(load->segname, "__TEXT"))
			find_section(path, load, origin);
		data += load->cmdsize;
	}
}
