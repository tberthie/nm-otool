/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:03:52 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 18:03:28 by tberthie         ###   ########.fr       */
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
	else if (!ft_strcmp(sect->sectname, SECT_DATA))
		sects[DATA] = offset;
	else if (!ft_strcmp(sect->sectname, SECT_BSS))
		sects[BSS] = offset;
	else if (!ft_strcmp(sect->sectname, SECT_COMMON))
		sects[COMMON] = offset;
}
