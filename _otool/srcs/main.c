/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:36:10 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 17:30:39 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int					main(int ac, char **av)
{
	t_file			*file;

	if (ac < 2)
		error_exit("Atleast one file must be specified.", 0);
	else
		while (ac-- >= 2 && ((file = get_file_data(*++av))))
			parse_file(file);
	return (0);
}
