/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:08:42 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 18:35:31 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "common.h"

void			parse_file(t_file *file);
void			parse_segments(t_file *file, const char *lib_path);
void			parse_sections(void *data, t_file *file, const char *lib_path);

#endif
