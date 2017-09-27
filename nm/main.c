/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 17:59:41 by tberthie          #+#    #+#             */
/*   Updated: 2017/09/27 17:36:30 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#include "libft.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

static void			nm(char *path, int fd)
{
	void			*data;
	struct stat		stat;
	size_t			len;
	t_header		*header;

	if (fstat(fd, &stat) == -1)
		ft_print(2, "ft_nm: %s: Failed to read file stats\n", path);
	else
	{
		len = (size_t)stat.st_size;
		if ((data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			ft_print(2, "ft_nm: %s: Failed to map file\n", path);
		else
		{
			if ((header = (t_header*)data)->magic == MH_MAGIC_64)
				parse_64(data + sizeof(t_header_64), data, header->ncmds);
			else if (header->magic == MH_MAGIC)
				parse_32(data + sizeof(t_header), data, header->ncmds);
			else
				ft_print(2, "ft_nm: %s: Not a valid object file\n", path);
			munmap(data, len);
		}
	}
}

static void			no_args(void)
{
	int		fd;

	if ((fd = open("a.out", O_RDONLY)) == -1)
		ft_print(2, "ft_nm: a.out: No such file or directory\n");
	else
		nm("a.out", fd);
}

int					main(int ac, char **av)
{
	int		fd;
	int		i;

	i = 1;
	if (ac == 1)
		no_args();
	while (i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			ft_print(2, "ft_nm: %s: No such file or directory\n", av[i]);
		else
		{
			if (ac > 2)
				ft_print(1, "\n%s:\n", av[i]);
			nm(av[i], fd);
		}
		i++;
	}
	return (0);
}
