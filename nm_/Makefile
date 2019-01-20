# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 13:34:07 by tberthie          #+#    #+#              #
#    Updated: 2019/01/20 21:53:58 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = ../nm

OBJS = $(addprefix objs/, $(addsuffix .o, \
		main lib lib2 parse tools print symtab ))

all: objs $(EXEC)

objs:
	mkdir objs

$(EXEC): $(OBJS)
	gcc -o $(EXEC) $(OBJS) -I includes

objs/%.o: srcs/%.c
	gcc -o $@ -c $< -Wall -Wextra -I includes

clean:
	rm -f $(EXEC)

fclean:
	rm -rf objs

re: fclean all
