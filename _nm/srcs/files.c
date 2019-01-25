/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:56:44 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 16:48:28 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			parse_files(t_file **files)
{
	t_file		*file;
	t_file		**objs;

	while (*files)
	{
		file = *files++;
		if (file->lib)
		{
			objs = ((t_lib*)file)->objs;
			while (*objs)
				parse_segments(*objs++);
		}
		else
			parse_segments(file);
	}
}
