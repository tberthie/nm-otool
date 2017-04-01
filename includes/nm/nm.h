/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 16:37:48 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/01 18:25:05 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <mach-o/loader.h>

typedef struct mach_header_64		t_header;
typedef struct segment_command_64	t_segment;

void		nm(char *path, int fd);

#endif
