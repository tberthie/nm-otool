/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:38:43 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 15:47:33 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "common.h"

typedef struct		s_sym {

	char			*name;
	char			symbol;
	size_t			value;

}					t_sym;

void				parse_files(t_file **files);
void				parse_segments(t_file *file);
void				parse_sections(void *data, t_file *file, int offset);
t_sym				**parse_symtab_32(t_symtab *symtab, t_file *file);
t_sym				**parse_symtab_64(t_symtab *symtab, t_file *file);

void				output(t_file **files, char nl);

void				ft_parrpush_syms(t_sym ***tab, t_sym *elem);

#endif
