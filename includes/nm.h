/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 16:37:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/09/15 13:56:46 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/stab.h>

typedef struct mach_header_64		t_header_64;
typedef struct mach_header			t_header;

typedef struct load_command			t_load;
typedef struct symtab_command		t_symtab;

typedef struct segment_command		t_seg;
typedef struct segment_command_64	t_seg_64;

typedef struct nlist_64				t_list_64;
typedef struct nlist				t_list;

typedef struct	s_symbol {
	char			*name;
	unsigned long	value;
	unsigned int	type;
	unsigned int	sect;
}				t_symbol;

enum	e_sections {
	TEXT, DATA, BSS, COMMON, OTHER
};

typedef struct	s_section {
	unsigned int	off;
	char			id;
	char			pad[3];
}				t_section;

void	parse_64(void *data, void *origin, unsigned int size);
void	parse_32(void *data, void *origin, unsigned int size);

void	add_section_32(void *origin, t_section ***sections, t_seg *seg);
char	*get_symbol(t_symbol *sym, t_section **sections, char cap);

#endif
