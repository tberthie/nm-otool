/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:58:25 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 18:03:22 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void				parse_segments(t_file *file)
{
	t_cmd			*cmd;
	size_t			cmds;
	size_t			offset;
	void			*payload;

	offset = 0;
	payload = 0;
	file->payload = ft_memalloc(sizeof(int) * 4);
	ft_memset(file->payload, -1, sizeof(int) * 4);
	cmds = ((t_header*)file->data)->ncmds;
	cmd = (t_cmd*)(file->data + (file->format == 32 ? sizeof(t_header) :
				sizeof(t_header_64)));
	while (cmds--)
	{
		if (cmd->cmd == LC_SYMTAB && file->format == 32)
			payload = parse_symtab_32((t_symtab*)cmd, file);
		else if (cmd->cmd == LC_SYMTAB && file->format == 64)
			payload = parse_symtab_64((t_symtab*)cmd, file);
		else if (cmd->cmd == LC_SEGMENT || cmd->cmd == LC_SEGMENT_64)
		{
			parse_sections(cmd, file, offset + 1);
			offset += file->format == 32 ? ((t_segment*)cmd)->nsects :
				((t_segment_64*)cmd)->nsects;
		}
		cmd = (void*)cmd + cmd->cmdsize;
	}
	free(file->payload);
	file->payload = payload;
}
