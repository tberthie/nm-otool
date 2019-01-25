# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 13:34:07 by tberthie          #+#    #+#              #
#    Updated: 2019/01/25 17:05:42 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = ../nm

OBJS = $(addprefix objs/, $(addsuffix .o, \
		main files segments sections symtab tools output ))

COMMON = $(addprefix ../_common/objs/, $(addsuffix .o, \
		 file lib tools tools2 tools3 ))

all: objs ../_common/objs $(EXEC)

objs:
	mkdir objs

../_common/objs:
	mkdir ../_common/objs

$(EXEC): $(OBJS) $(COMMON)
	gcc -o $(EXEC) $(OBJS) $(COMMON)

../_common/objs/%.o: ../_common/srcs/%.c
	gcc -o $@ -c $< -Wall -Wextra -I includes -I ../_common/includes -g

objs/%.o: srcs/%.c
	gcc -o $@ -c $< -Wall -Wextra -I includes -I ../_common/includes -g

clean:
	rm -rf objs
	rm -rf ../_common/objs

fclean: clean
	rm -f $(EXEC)

re: fclean all
