/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 17:59:41 by tberthie          #+#    #+#             */
/*   Updated: 2017/04/01 16:38:26 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#include "libft.h"

#include <fcntl.h>

int			main(int ac, char **av)
{
	int		fd;
	int		i;

	i = 1;
	while (i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) == -1)
			ft_printf(2, "ft_nm: %s: No such file or directory.\n", av[i]);
		else
		{
			if (ac > 2)
				ft_printf(1, "\n%s:\n", av[i]);
			nm(av[i], fd);
		}
		i++;
	}
	return (0);
}
