/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:08:54 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/19 22:11:55 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#include "libft.h"

#include <mach-o/nlist.h>

static void		dump(void *addr, unsigned char *data, unsigned int size)
{
	unsigned int	off;

	off = 16;
	printf("%08x\t", (unsigned int)addr);
	while (size--)
	{
		printf("%02x ", *data++);
		off--;
		if (!off)
		{
			off = 16;
			printf("\n");
			printf("%08x\t", (unsigned int)(addr += 16));
		}
	}
	if (off != 16)
		printf("\n");

}

static void		find_section(char *path, t_segment_64 *seg, void *origin)
{
	unsigned int	size;
	t_section_64		*sec;

	ft_printf(1, "%s:\nContents of (__TEXT,__text) section\n", path);
	sec = (void*)seg + sizeof(t_segment_64);
	size = seg->nsects;
	while (ft_strcmp(sec->sectname, "__text") && size--)
		sec += sizeof(t_section_64);
	if (size)
		dump(sec->addr, origin + sec->offset, sec->size);
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
