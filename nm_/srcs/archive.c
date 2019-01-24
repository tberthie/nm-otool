/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:40:10 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/24 17:41:35 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char			*get_object_name(t_arch *arch)
{
	char			*name;
	size_t			len;

	if (!ft_memcmp(arch->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
	{
		len = ft_atoi((void*)(arch->ar_name) + ft_strlen(AR_EFMT1));
		if (!(name = ft_memalloc(len + 3)))
			error_exit("Malloc failed.", 0);
		name[0] = '(';
		ft_memcpy(name + 1, (void*)arch + sizeof(t_arch), len);
		name[ft_strlen(name)] = ')';
		return (name);
	}
	len = 0;
	while (arch->ar_name[len] != ' ' && len < 16)
		len++;
	if (!(name = ft_memalloc(len + 3)))
		error_exit("Malloc failed.", 0);
	name[0] = '(';
	ft_memcpy(name + 1, arch->ar_name, len);
	name[ft_strlen(name)] = ')';
	return (name);
}

void				parse_archive(t_file *file)
{
	t_arch			*arch;
	t_file			*new_file;

	file->arch = 64;
	arch = (t_arch*)(file->data + SARMAG);
	while ((void*)arch < (void*)file->data + file->size)
	{
		if (!(new_file = malloc(sizeof(t_file))))
			error_exit("Malloc failed.", 0);
		ft_memcpy(new_file, file, sizeof(t_file));
		if (!(new_file->symtab = malloc(8)))
			error_exit("Malloc failed.", 0);
		new_file->symtab[0] = 0;
		new_file->path = ft_strdup(file->path);
		ft_memset(new_file->sect, 0, 256);
		ft_strpush(&(new_file->path), get_object_name(arch));
		new_file->data = (void*)arch + sizeof(t_arch) + (!ft_memcmp(arch->ar_name,
			AR_EFMT1, ft_strlen(AR_EFMT1)) ? ft_atoi(arch->ar_name + ft_strlen(AR_EFMT1)) : 0);
		new_file->size = ft_atoi(arch->ar_size) - (!ft_memcmp(arch->ar_name,
			AR_EFMT1, ft_strlen(AR_EFMT1)) ? ft_atoi(arch->ar_name + ft_strlen(AR_EFMT1)) : 0);
		arch = (void*)new_file->data + new_file->size;
		if (!parse_loader(new_file))
			print_symbols(new_file, 1);
		// free new_file + munmap
	}
}
