/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:04:45 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/20 20:54:43 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char		get_sect(t_file *file, int offset, int ext)
{
	if (file->sect[offset] == TEXT)
		return ("Tt"[ext]);
	else if (file->sect[offset] == DATA)
		return ("Dd"[ext]);
	else if (file->sect[offset] == BSS)
		return ("Bb"[ext]);
	else if (file->sect[offset] == COMMON)
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
	else if (type == N_SECT)
	{
		return (get_sect(file, file->arch == 32 ? list->n_sect :
					((t_list_64*)list)->n_sect, ext));
	}
	return (0);
}

void			parse_symtab_32(t_symtab *symtab, t_file *file)
{
	t_symbol	*symbol;
	t_list		*list;
	int			count;
	char		symbol_c;

	count = symtab->nsyms;
	list = (void*)file->data + symtab->symoff;
	while (count--)
	{
		if (list->n_un.n_strx && (symbol_c = get_symbol(file, (t_list*)list,
				list->n_type & N_TYPE, list->n_type & N_EXT ? 0 : 1)))
		{
			if (!(symbol = malloc(sizeof(t_symbol))))
				error_exit("Malloc failed.", 0);
			symbol->value = list->n_value;
			symbol->symbol = symbol_c;
			symbol->name = ft_strdup(file->data + symtab->stroff +
					list->n_un.n_strx);
			ft_arrpush_ascii((void***)&(file->symtab), symbol);
		}
		list = (void*)list + sizeof(t_list);
	}
}

void			parse_symtab_64(t_symtab *symtab, t_file *file)
{
	t_symbol	*symbol;
	t_list_64	*list;
	int			count;
	char		symbol_c;

	count = symtab->nsyms;
	list = (void*)file->data + symtab->symoff;
	while (count--)
	{
		if (list->n_un.n_strx && (symbol_c = get_symbol(file, (t_list*)list,
				list->n_type & N_TYPE, list->n_type & N_EXT ? 0 : 1)))
		{
			if (!(symbol = malloc(sizeof(t_symbol))))
				error_exit("Malloc failed.", 0);
			symbol->value = list->n_value;
			symbol->symbol = symbol_c;
			symbol->name = ft_strdup(file->data + symtab->stroff +
					list->n_un.n_strx);
			ft_arrpush_ascii((void***)&(file->symtab), symbol);
		}
		list = (void*)list + sizeof(t_list_64);
	}
}
