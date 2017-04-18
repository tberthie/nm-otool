/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:17:08 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/18 16:31:52 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include <stdlib.h>
# include <mach-o/loader.h>

typedef struct mach_header_64		t_header_64;
typedef struct mach_header			t_header;

typedef struct load_command			t_load;

typedef struct segment_command_64	t_segment_64;
typedef struct segment_command		t_segment;

typedef struct section_64			t_section_64;
typedef struct section				t_section;

#endif
