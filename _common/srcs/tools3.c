/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:27:26 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 16:44:29 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void			error(const char *format, const char *data)
{
	write(2, "error: ", 7);
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 's')
		{
			write(2, data, ft_strlen(data));
			format += 2;
		}
		else
			write(2, format++, 1);
	}
	write(2, "\n", 1);
}

void			error_exit(const char *format, const char *data)
{
	error(format, data);
	exit(1);
}

size_t			get_file_size(int fd)
{
	struct stat	file_stats;

	if (fstat(fd, &file_stats) != 0)
		return (0);
	return (file_stats.st_size);
}
