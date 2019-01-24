/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:13:34 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/24 17:59:44 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void			load_data_seg(t_file *file, t_segment *seg, int offset,
		int sects)
{
	t_section		*sect;

	sect = (void*)seg + (file->arch == 32 ? sizeof(t_segment) :
			sizeof(t_segment_64));
	if (!ft_strcmp(sect->sectname, SECT_TEXT))
		ft_memset(file->sect + offset, TEXT, 1);
	else if (!ft_strcmp(sect->sectname, SECT_DATA))
		ft_memset(file->sect + offset, DATA, 1);
	else if (!ft_strcmp(sect->sectname, SECT_BSS))
		ft_memset(file->sect + offset, BSS, 1);
	else if (!ft_strcmp(sect->sectname, SECT_COMMON))
		ft_memset(file->sect + offset, COMMON, 1);
}

static void			load_seg(t_file *file, t_segment *seg, int count)
{
	int				i;
	char			type;
	char			*name;

	type = 0;
	i = file->arch == 32 ? seg->nsects : ((t_segment_64*)seg)->nsects;
	name = file->arch == 32 ? seg->segname : ((t_segment_64*)seg)->segname;
	load_data_seg(file, seg, count, i);
}

static void			parse_cmds(t_file *file)
{
	t_cmd			*cmd;
	size_t			cmd_count;
	int				sect_count;

	sect_count = 0;
	cmd_count = ((t_header*)file->data)->ncmds;
	cmd = (t_cmd*)(file->data + (file->arch == 32 ? sizeof(t_header) :
		sizeof(t_header_64)));
	while (cmd_count--)
	{
		if (cmd->cmd == LC_SYMTAB && file->arch == 32)
			parse_symtab_32((t_symtab*)cmd, file);
		else if (cmd->cmd == LC_SYMTAB && file->arch == 64)
			parse_symtab_64((t_symtab*)cmd, file);
		else if (cmd->cmd == LC_SEGMENT || cmd->cmd == LC_SEGMENT_64)
		{
			load_seg(file, (t_segment*)cmd, sect_count);
			sect_count += file->arch == 32 ? ((t_segment*)cmd)->nsects :
				((t_segment_64*)cmd)->nsects;
		}
		cmd = (void*)cmd + cmd->cmdsize;
	}
}

char				parse_loader(t_file *file)
{
	unsigned int	magic;

	magic = *(unsigned int*)file->data;
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		file->arch = 32;
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		file->arch = 64;
	else if (!ft_memcmp(file->data, ARMAG, SARMAG))
	{
		parse_archive(file);
		return (0);
	}
	else
	{
		error("%s: Invalid file type.", file->path);
		return (1);
	}
	parse_cmds(file);
	return (0);
}

void				parse_file(const char *path, char multi)
{
	t_file			*file;

	if (!(file = malloc(sizeof(t_file))))
		error_exit("Malloc failed.", 0);
	file->path = ft_strdup(path);
	if (!(file->symtab = malloc(8)))
		error_exit("Malloc failed.", 0);
	else if ((file->fd = open(path, O_RDONLY)) < 0)
		error("%s: No such file or directory.", path);
	else if (!(file->size = get_file_size(file->fd)) ||
			(file->data = mmap(NULL, file->size, PROT_READ, MAP_FILE |
			MAP_PRIVATE, file->fd, 0)) == MAP_FAILED)
		error("%s: File parsing failed.", path);
	else
	{
		file->symtab[0] = 0;
		ft_memset(file->sect, 0, 256);
		if (!parse_loader(file))
			print_symbols(file, multi);
		munmap(file->data, file->size);
		close(file->fd);
	}
}
