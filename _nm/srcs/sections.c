/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:03:52 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 16:47:44 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			parse_sections(void *data, t_file *file, int offset)
{
	int			*sects;
	t_section	*sect;

	sects = (int*)file->payload;
	sect = data + (file->format == 32 ? sizeof(t_segment) :
		sizeof(t_segment_64));
	if (!ft_strcmp(sect->sectname, SECT_TEXT))
		sects[TEXT] = offset;
	else if (!ft_strcmp(sect->sectname, SECT_TEXT))
		sects[DATA] = offset;
	else if (!ft_strcmp(sect->sectname, SECT_TEXT))
		sects[BSS] = offset;
	else if (!ft_strcmp(sect->sectname, SECT_TEXT))
		sects[COMMON] = offset;
}
