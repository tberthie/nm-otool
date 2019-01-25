/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:03:52 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 18:42:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void			print_hex_pad(size_t offset, int padding)
{
	size_t			i;

	padding -= 1;
	i = 1;
	while (offset / i >= 16)
	{
		i *= 16;
		padding--;
	}
	while (padding--)
		write(1, "0", 1);
	while (i)
	{
		write(1, &HEX[offset / i % 16], 1);
		i /= 16;
	}
	write(1, "\t", 1);
}

static void			print_data(void *data, size_t len)
{
	unsigned char	*d;
	size_t			offset;

	offset = 0;
	d = data;
	while (len--)
	{
		if (!(offset % 16))
			print_hex_pad(offset, 16);
		write(1, &HEX[*d / 16 % 16], 1);
		write(1, &HEX[*d++ % 16], 1);
		write(1, " ", 1);
		if (!(++offset % 16) && len)
			write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

void				parse_sections(void *data, t_file *file, const char *lib_path)
{
	t_section		*sect;

	sect = data + (file->format == 32 ? sizeof(t_segment) :
		sizeof(t_segment_64));
	if (!ft_strcmp(sect->sectname, SECT_TEXT) && !ft_strcmp(sect->segname,
				SEG_TEXT))
	{
		if (lib_path)
		{
			write(1, lib_path, ft_strlen(lib_path));
			write(1, "(", 1);
			write(1, file->path, ft_strlen(file->path));
			write(1, ")", 1);
		}
		else
			write(1, file->path, ft_strlen(file->path));
		write(1, ":\nContents of (__TEXT,__text) section\n", 38);
		if (file->format == 32)
			print_data(file->data + sect->offset, sect->size);
		else
			print_data(file->data + ((t_section_64*)sect)->offset,
					((t_section_64*)sect)->size);
	}
}
