# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2017/05/09 02:32:41 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ONM = $(addsuffix .o, $(addprefix objs/nm/, main parse_32 parse_64))
OTOOL = $(addsuffix .o, $(addprefix objs/otool/, main parse_32 parse_64 utl))

NM = ft_nm
TOOL = ft_otool

all: objs $(NM) $(TOOL)

objs:
	mkdir objs
	mkdir objs/nm
	mkdir objs/otool

$(NM): $(ONM)
	make -C libft
	gcc -o $(NM) $(ONM) libft/libft.a

$(TOOL): $(OTOOL)
	make -C libft
	gcc -o $(TOOL) $(OTOOL) libft/libft.a

objs/nm/%.o: nm/%.c
	gcc -o $@ -c $< -I includes -I libft -Weverything -Wno-pointer-arith

objs/otool/%.o: otool/%.c
	gcc -o $@ -c $< -I includes -I libft -Weverything -Wno-pointer-arith

clean:
	rm -rf objs

fclean: clean
	make -C libft fclean
	rm -f $(NM)
	rm -f $(TOOL)

re: fclean all
