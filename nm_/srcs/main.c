/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:36:10 by tberthie          #+#    #+#             */
/*   Updated: 2019/01/20 20:39:58 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <stdio.h>

int					main(int ac, char **av)
{
	char			multi;

	multi = ac > 2;
	if (ac == 1)
		parse_file("a.out", 0);
	while (ac-- >= 2)
		parse_file(*++av, multi);
	return (0);
}
