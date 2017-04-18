/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 16:37:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/18 13:50:19 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <mach-o/loader.h>

typedef struct mach_header_64		t_header_64;
typedef struct mach_header			t_header;

typedef struct load_command			t_load;
typedef struct symtab_command		t_symtab;

typedef struct nlist_64				t_list_64;
typedef struct nlist				t_list;

typedef struct	s_symbol {
	char			*name;
	unsigned long	value;
	unsigned int	type;
	unsigned int	sect;
}				t_symbol;

void	parse_64(void *data, void *origin, unsigned int size);
void	parse_32(void *data, void *origin, unsigned int size);

#endif
