/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:58:25 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 18:03:32 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void				parse_segments(t_file *file, const char *lib_path)
{
	t_cmd			*cmd;
	size_t			cmds;

	cmds = ((t_header*)file->data)->ncmds;
	cmd = (t_cmd*)(file->data + (file->format == 32 ? sizeof(t_header) :
				sizeof(t_header_64)));
	while (cmds--)
	{
		if (cmd->cmd == LC_SEGMENT || cmd->cmd == LC_SEGMENT_64)
			parse_sections(cmd, file, lib_path);
		cmd = (void*)cmd + cmd->cmdsize;
	}
}
