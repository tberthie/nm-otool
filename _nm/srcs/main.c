/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:36:10 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/25 17:03:59 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int					main(int ac, char **av)
{
	t_file			**files;
	t_file			*file;
	char			nl;

	files = ft_memalloc(sizeof(void*));
	*files = 0;
	if (ac == 1 && (file = get_file_data("a.out")))
		ft_parrpush((void***)&files, file);
	while (ac-- >= 2)
		if ((file = get_file_data(*++av)))
			ft_parrpush((void***)&files, file);
	nl = (*files && (*(files + 1) || (*files)->lib));
	parse_files(files);
	output(files, nl);
	return (0);
}
