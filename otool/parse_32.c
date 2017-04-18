/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:13:50 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/18 17:06:41 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#include "libft.h"

#include <mach-o/nlist.h>

static void		output(t_segment *seg, void *origin)
{
	unsigned int	size;
	unsigned char	*data;
	unsigned int	off;
	t_section		*sec;

	ft_printf(1, "ft_otool:\nContents of (__TEXT,__text) section\n");
	sec = (void*)seg + sizeof(t_segment);
	size = seg->nsects;
	while (ft_strcmp(sec->sectname, "__text") && size--)
		sec += sizeof(struct section);
	if (size)
	{
		data = origin + sec->offset;
		size = sec->size;
		off = 16;
		while (size--)
		{
			printf("%02x ", *data++);
			off--;
			if (!off)
			{
				off = 16;
				printf("\n");
			}
		}
		if (off != 16)
			printf("\n");
	}
}

void			parse_32(void *data, void *origin, unsigned int size)
{
	t_segment		*load;

	while (size--)
	{
		load = (t_segment*)data;
		if (load->cmd == LC_SEGMENT && !ft_strcmp(load->segname, "__TEXT"))
			output(load, origin);
		data += load->cmdsize;
	}
}
