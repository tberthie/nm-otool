/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:13:50 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/18 22:47:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#include "libft.h"

#include <mach-o/nlist.h>

static void		print_symbol(t_symbol *sym, char **sections)
{
	unsigned char	typem;
	char			cap;

	typem = sym->type & N_TYPE;
	cap = sym->type & N_EXT;
	if (typem == N_SECT)
		//get section
		ft_printf(1, cap ? "T" : "t");
	else if (typem == N_ABS)
		ft_printf(1, "A");
	else if (typem == N_INDR)
		ft_printf(1, cap ? "I" : "i");
	else
		ft_printf(1, cap ? "U" : "u");
}

static void		output(t_symbol **sym, char **sections)
{
	int		i;

	i = 0;
	while (sym[i])
	{
//		if ((*sym)->value)
//			ft_printf(1, "%d ", (*sym)->value);
//		else
//			ft_printf(1, type == 64 ? "\t\t " : "\t ");
//		print_symbol(*sym);
		ft_printf(1, " %s\n", sym[i]->name);
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
	while (nsyms--)
	{
		symbol = (t_symbol*)ft_m(sizeof(t_symbol));
		symbol->name = origin + symtab->stroff + list->n_un.n_strx;
		symbol->type = list->n_type;
		symbol->value =  list->n_value;
		ft_parrpush((void***)&syms, symbol);
		list = (void*)list + sizeof(t_list);
	}
	return (syms);
}

void			parse_32(void *data, void *origin, unsigned int size)
{
	t_load			*load;
	char			**sections;

	sections = (char**)ft_parrnew();
	while (size--)
	{
		load = (t_load*)data;
		if (load->cmd == LC_SYMTAB)
			output(parse_symbols((t_symtab*)load, origin), sections);
//		else if (load->cmd == LC_SEGMENT)
//			parse_sections(&sections, load, origin);
		data += load->cmdsize;
	}
	ft_parrfree((void**)sections);
}
