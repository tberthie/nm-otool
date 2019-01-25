/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:47:21 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 18:28:21 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		print_nbr_pad(size_t value, int padding)
{
	size_t		i;

	i = 1;
	padding -= 1;
	while (value / i >= 16)
	{
		i *= 16;
		padding--;
	}
	while (padding--)
		write(1, "0", 1);
	while (i)
	{
		write(1, &HEX[value / i % 16], 1);
		i /= 16;
	}
}

static void		output_file(t_file *file)
{
	t_sym		**syms;

	syms = (t_sym**)file->payload;
	while (*syms)
	{
		if ((*syms)->symbol == 'u' || (*syms)->symbol == 'U')
			write(1, "                ", file->format == 32 ? 8 : 16);
		else
			print_nbr_pad((*syms)->value, file->format / 4);
		write(1, " ", 1);
		write(1, &((*syms)->symbol), 1);
		write(1, " ", 1);
		write(1, (*syms)->name, ft_strlen((*syms)->name));
		write(1, "\n", 1);
		syms++;
	}
}

void			output(t_file **files, char nl)
{
	t_file		*file;
	t_file		**objs;

	while (*files)
	{
		file = *files;
		if (file->lib)
		{
			objs = ((t_lib*)file)->objs;
			while (*objs)
			{
				write(1, "\n", 1);
				write(1, file->path, ft_strlen(file->path));
				write(1, "(", 1);
				write(1, (*objs)->path, ft_strlen((*objs)->path));
				write(1, "):\n", 3);
				output_file(*objs);
				objs++;
			}
		}
		else
		{
			if (nl)
			{
				write(1, "\n", 1);
				write(1, file->path, ft_strlen(file->path));
				write(1, ":\n", 2);
			}
			output_file(*files);
		}
		files++;
	}
}
