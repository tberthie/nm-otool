/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:04:45 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 16:59:14 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char		get_sect(t_file *file, int offset, int ext)
{
	int			*sect;

	sect = (int*)file->payload;
	if (sect[TEXT] == offset)
		return ("Tt"[ext]);
	else if (sect[DATA] == offset)
		return ("Dd"[ext]);
	else if (sect[BSS] == offset)
		return ("Bb"[ext]);
	else if (sect[COMMON] == offset)
		return ("Cc"[ext]);
	return ("Ss"[ext]);
}

static char		get_symbol(t_file *file, t_list *list, unsigned int type,
		int ext)
{
	if (type == N_UNDF)
		return ("Uu"[ext]);
	else if (type == N_ABS)
		return ("Aa"[ext]);
	else if (type == N_INDR)
		return ("Ii"[ext]);
	return (get_sect(file, file->format == 32 ? list->n_sect :
		((t_list_64*)list)->n_sect, ext));
}

t_sym			**parse_symtab_32(t_symtab *symtab, t_file *file)
{
	t_sym		**syms;
	t_sym		*symbol;
	int			nsyms;
	t_list		*list;

	nsyms = symtab->nsyms;
	list = file->data + symtab->symoff;
	syms = ft_memalloc(sizeof(void*));
	*syms = 0;
	while (nsyms--)
	{
		if (list->n_un.n_strx)
		{
			symbol = ft_memalloc(sizeof(t_sym));
			symbol->name = ft_strdup(file->data + symtab->stroff +
					list->n_un.n_strx);
			symbol->value = list->n_value;
			symbol->symbol = get_symbol(file, list, list->n_type & N_TYPE,
					list->n_type & N_EXT ? 0 : 1);
			ft_parrpush_syms(&syms, symbol);
		}
		list = (void*)list + sizeof(t_list);
	}
	return (syms);
}

t_sym			**parse_symtab_64(t_symtab *symtab, t_file *file)
{
	t_sym		**syms;
	t_sym		*symbol;
	int			nsyms;
	t_list_64	*list;

	nsyms = symtab->nsyms;
	list = file->data + symtab->symoff;
	syms = ft_memalloc(sizeof(void*));
	*syms = 0;
	while (nsyms--)
	{
		if (list->n_un.n_strx)
		{
			symbol = ft_memalloc(sizeof(t_sym));
			symbol->name = ft_strdup(file->data + symtab->stroff +
					list->n_un.n_strx);
			symbol->value = list->n_value;
			symbol->symbol = get_symbol(file, (t_list*)list,
					list->n_type & N_TYPE, list->n_type & N_EXT ? 0 : 1);
			ft_parrpush_syms(&syms, symbol);
		}
		list = (void*)list + sizeof(t_list_64);
	}
	return (syms);
}
