/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:56:42 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 17:36:30 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char		*get_object_name(t_arch *arch)
{
	char		*name;
	size_t		len;

	if (!ft_memcmp(arch->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
	{
		len = ft_atoi((void*)(arch->ar_name) + ft_strlen(AR_EFMT1));
		if (!(name = ft_memalloc(len + 1)))
			error_exit("Malloc failed.", 0);
		ft_memcpy(name, (void*)arch + sizeof(t_arch), len);
		return (name);
	}
	len = 0;
	while (arch->ar_name[len] != ' ' && len < 16)
		len++;
	if (!(name = ft_memalloc(len + 1)))
		error_exit("Malloc failed.", 0);
	ft_memcpy(name, arch->ar_name, len);
	return (name);
}

static void		load_lib_objects(t_lib *lib, void *data, size_t size)
{
	int			overflow;
	char		*name;
	t_arch		*arch;
	t_file		*file;

	arch = data + SARMAG;
	while ((void*)arch + sizeof(t_arch) < (void*)data + size)
	{
		overflow = (!ft_memcmp(arch->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)) ? 1 : 0) *
			ft_atoi((void*)arch->ar_name + ft_strlen(AR_EFMT1));
		name = get_object_name(arch);
		if ((file = load_file(name, (void*)arch + sizeof(t_arch) + overflow,
						ft_atoi(arch->ar_size) - overflow)))
			ft_parrpush((void***)&(lib->objs), file);
		free(name);
		arch = (void*)arch + sizeof(t_arch) + ft_atoi(arch->ar_size);
	}
}

t_lib			*load_lib(const char *path, void *data, size_t size)
{
	t_lib		*lib;

	lib = ft_memalloc(sizeof(t_lib));
	lib->lib = 1;
	lib->path = ft_strdup(path);
	lib->objs = ft_memalloc(sizeof(void*));
	*(lib->objs) = 0;
	load_lib_objects(lib, data, size);
	return (lib);
}
