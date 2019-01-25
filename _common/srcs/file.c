/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:42:17 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 17:24:50 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char			check_file_magic(void *data)
{
	unsigned int	magic;

	magic = *(int*)data;
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (32);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (64);
	return (0);
}

t_file				*load_file(const char *path, void *data, size_t size)
{
	t_file			*file;
	char			format;

	if (!(format = check_file_magic(data)))
		return (0);
	file = ft_memalloc(sizeof(t_file));
	file->format = format;
	file->path = path ? ft_strdup(path) : 0;
	file->data = data;
	file->size = size;
	return (file);
}


void				*get_file_data(const char *path)
{
	int				fd;
	size_t			size;
	void			*data;

	if ((fd = open(path, O_RDONLY)) < 0)
		error("%s: Failed to open file.", path);
	else if (!(size = get_file_size(fd)) || (data = mmap(0, size,
			PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		error("%s: Failed to read from file.", path);
	else
	{
		close(fd);
		if (!ft_memcmp(data, ARMAG, SARMAG))
			return (load_lib(path, data, size));
		else
			return (load_file(path, data, size));
	}
	return (0);
}
