/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:16:20 by tberthie          #+#    #+#             */
/*   Updated: 2017/09/29 18:26:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

#include "libft.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

static void			otool(char *path, int fd)
{
	void			*data;
	struct stat		stat;
	size_t			len;
	t_header		*header;

	if (fstat(fd, &stat) == -1)
		ft_print(2, "ft_otool: %s: Failed to read file stats\n", path);
	else
	{
		len = (size_t)stat.st_size;
		if ((data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			ft_print(2, "ft_otool: %s: Failed to map file\n", path);
		else
		{
			if ((header = (t_header*)data)->magic == MH_MAGIC_64)
				parse_64(path, data + sizeof(t_header_64), data, header->ncmds);
			else if ((header = (t_header*)data)->magic == MH_MAGIC)
				parse_32(path, data + sizeof(t_header), data, header->ncmds);
			else
				ft_print(2, "ft_otool: %s: Not a valid object file\n", path);
			ft_print(2, "%p\n", header->magic);
			munmap(data, len);
		}
	}
}

int					main(int ac, char **av)
{
	int		fd;
	int		i;

	i = 1;
	if (ac == 1)
		ft_print(2, "ft_otool: Atleast one file must be specified\n");
	while (i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			ft_print(2, "ft_otool: %s: No such file or directory\n", av[i]);
		else
			otool(av[i], fd);
		i++;
	}
	return (0);
}
