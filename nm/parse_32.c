/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:13:50 by tberthie          #+#    #+#             */
/*   Updated: 2017/09/09 15:58:46 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#include "libft.h"

#include <mach-o/nlist.h>

static void			print_symbol(t_symbol *sym, t_section **sections)
{
	unsigned char	typem;
	char			cap;

	typem = sym->type & N_TYPE;
	cap = sym->type & N_EXT;
	if (typem == N_SECT)
		ft_print(1, get_symbol(sym, sections, cap));
	else if (typem == N_ABS)
		ft_print(1, "A");
	else if (typem == N_INDR)
		ft_print(1, cap ? "I" : "i");
	else
		ft_print(1, cap ? "U" : "u");
}

static void			output(t_symbol **sym, t_section **sections)
{
	int		i;

	i = 0;
	while (sym[i])
	{
		if (sym[i]->value)
			ft_printf("%08x ", sym[i]->value);
		else
			ft_print(1, "         ");
		print_symbol(sym[i], sections);
		ft_print(1, " %s\n", sym[i]->name);
		i++;
	}
	ft_parrfree((void**)sym);
}

static t_symbol		**parse_symbols(t_symtab *symtab, void *origin)
{
	t_symbol		**syms;
	t_symbol		*symbol;
	unsigned int	nsyms;
	t_list			*list;

	syms = (t_symbol**)ft_parrnew();
	nsyms = symtab->nsyms;
	list = origin + symtab->symoff;
	ft_printf("         SYMTAB %p\n", (void*)origin + symtab->symoff);
	while (nsyms--)
	{
		symbol = (t_symbol*)ft_m(sizeof(t_symbol));
		symbol->name = origin + symtab->stroff + list->n_un.n_strx;
		symbol->type = list->n_type;
		symbol->value = list->n_value;
		ft_parrpush((void***)&syms, symbol);
		list = (void*)list + sizeof(t_list);
	}
	return (syms);
}

static t_symbol		**sort(t_symbol **sym)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < ft_parrlen((void**)sym) - 1)
	{
		j = i + 1;
		while (j < ft_parrlen((void**)sym))
		{
			if (ft_strcmp(sym[i]->name, sym[j]->name) > 0)
				ft_ptrswap((void**)&sym[i], (void**)&sym[j]);
			j++;
		}
		i++;
	}
	return (sym);
}

void				parse_32(void *data, void *origin, unsigned int size)
{
	t_load			*load;
	t_section		**sections;

	sections = (t_section**)ft_parrnew();
	while (size--)
	{
		load = (t_load*)data;
		if (load->cmd == LC_SYMTAB)
			output(sort(parse_symbols((t_symtab*)load, origin)), sections);
		if (load->cmd == LC_SEGMENT)
			add_section_32(origin, &sections, (t_seg*)load);
		data += load->cmdsize;
	}
}
