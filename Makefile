# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2019/01/25 17:05:46 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: nm otool

nm:
	@make -C _nm

otool:
	@make -C _otool

clean:
	@make -C _nm clean
	@make -C _otool clean

fclean: clean
	@make -C _nm fclean
	@make -C _otool fclean

re: fclean all
