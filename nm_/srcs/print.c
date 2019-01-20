/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:50:05 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/20 20:35:24 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		print(const char *format, const char *data)
{
	while (*format)
	{
		if (*format == '%' && *(format + 1) == 's')
		{
			write(1, data, ft_strlen(data));
			format += 2;
		}
		else
			write(1, format++, 1);
	}
}

static void		print_hex(size_t value, int padding)
{
	size_t		i;

	if (!value)
		while (padding--)
			write(1, "  ", 2);
	else
	{
		i = 1;
		padding = padding * 2 - 1;
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
}

void			print_symbols(t_file *file, char multi)
{
	t_symbol	**symtab;

	symtab = file->symtab;
	if (multi)
		print("\n%s:\n", file->path);
	while (*symtab)
	{
		print_hex((*symtab)->value, file->arch == 32 ? 4 : 8);
		write(1, " ", 1);
		write(1, &((*symtab)->symbol), 1);
		print(" %s", (*symtab)->name);
		write(1, "\n", 1);
		symtab++;
	}
}
