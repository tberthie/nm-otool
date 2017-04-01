/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:18:39 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/01 18:24:59 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#include "libft.h"

#include <sys/stat.h>
#include <sys/mman.h>

#include <mach-o/nlist.h>

static void		map(void *data, unsigned int size)
{
	t_segment	*seg;

	while (size--)
	{
		seg = (t_segment*)data;
		ft_printf(1, "%s\n", seg->segname);
		data += seg->cmdsize;
	}
}

void			nm(char *path, int fd)
{
	void			*data;
	struct stat		stat;
	size_t			len;
	t_header		*header;

	if (fstat(fd, &stat) == -1)
		ft_printf(2, "ft_nm: %s: Failed to read file stats.\n", path);
	else
	{
		len = (size_t)stat.st_size;
		if ((data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			ft_printf(2, "ft_nm: %s: Failed to map file.\n", path);
		else
		{
			if ((header = (t_header*)data)->magic == 0xfeedfacf)
				map(data + sizeof(t_header), header->ncmds);
			else
				ft_printf(2, "ft_nm: %s: Not a valid object file.\n", path);
			munmap(data, len);
		}
	}
}
