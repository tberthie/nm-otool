/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:13:34 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/20 21:51:55 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void			load_data_seg(t_file *file, t_segment *seg, int offset,
		int sects)
{
	t_section		*sect;

	sect = (void*)seg + (file->arch == 32 ? sizeof(t_segment) :
			sizeof(t_segment_64));
	while (sects--)
	{
		if (!ft_strcmp(sect->sectname, SECT_DATA))
			file->sect[offset++] = DATA;
		else if (!ft_strcmp(sect->sectname, SECT_BSS))
			file->sect[offset++] = BSS;
		else if (!ft_strcmp(sect->sectname, SECT_COMMON))
			file->sect[offset++] = COMMON;
		else
			file->sect[offset++] = 0;
		sect = (void*)sect + (file->arch == 32 ? sizeof(t_section) :
			sizeof(t_section_64));
	}
}

static void			load_seg(t_file *file, t_segment *seg, int count)
{
	int				i;
	char			type;

	type = 0;
	i = file->arch == 32 ? seg->nsects : ((t_segment_64*)seg)->nsects;
	if (!ft_strcmp(seg->segname, SEG_TEXT))
		ft_memset(file->sect + count, TEXT, i);
	else if (!ft_strcmp(seg->segname, SEG_DATA))
		load_data_seg(file, seg, count, i);
	else
		ft_memset(file->sect + count, 0, i);
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

static void			parse_loader(t_file *file)
{
	unsigned int	magic;

	magic = *(unsigned int*)file->data;
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		file->arch = 32;
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		file->arch = 64;
/*	else if (!ft_memcmp(file->data, "!<arch>\n", 8))
	{
		t_arch		*arch;
		size_t		size;
	
		arch = file->data + 8;
		while (arch)
		{
			printf("[%16.s] - [%10.s]\n", arch->name, arch->size);
			size = ft_readnbr(arch->size);
			arch = (void*)arch + 60 + size;
		}
	}*/
	else
	{
		error("%s: Invalid file type.", file->path);
		return ;
	}
	parse_cmds(file);
}

void				parse_file(const char *path, char multi)
{
	t_file			file;

	file.path = path;
	if (!(file.symtab = malloc(8)))
		error_exit("Malloc failed.", 0);
	else if ((file.fd = open(path, O_RDONLY)) < 0)
		error("%s: No such file or directory.", path);
	else if (!(file.size = get_file_size(file.fd)) ||
			(file.data = mmap(NULL, file.size, PROT_READ, MAP_FILE |
			MAP_PRIVATE, file.fd, 0)) == MAP_FAILED)
		error("%s: File parsing failed.", path);
	else
	{
		file.symtab[0] = 0;
		parse_loader(&file);
		print_symbols(&file, multi);
		munmap(file.data, file.size);
		close(file.fd);
	}
}
