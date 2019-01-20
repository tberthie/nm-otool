# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2019/01/15 17:07:59 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: nm otool

nm:
	make -C nm_

otool:
	make -C otool_

clean:
	make -C nm_ clean
	make -C otool_ clean

fclean: clean
	make -C nm_ fclean
	make -C otool_ fclean

re: fclean all
