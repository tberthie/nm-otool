/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:28:18 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 18:41:36 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void			parse_file(t_file *file)
{
	t_file		**objs;

	if (file->lib)
	{
		objs = ((t_lib*)file)->objs;
		write(1, "Archive : ", 10);
		write(1, file->path, ft_strlen(file->path));
		write(1, "\n", 1);
		while (*objs)
			parse_segments(*objs++, file->path);
	}
	else
		parse_segments(file, 0);
}
