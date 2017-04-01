# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 22:18:00 by tberthie          #+#    #+#              #
#    Updated: 2017/03/27 13:30:23 by tberthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ONM = $(addsuffix .o, $(addprefix objs/nm/, main nm))
OTOOL = $(addsuffix .o, $(addprefix objs/otool/, main))

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
	gcc -o $@ -c $< -I includes/nm -I libft -Weverything

objs/otool/%.o: otool/%.c
	gcc -o $@ -c $< -I includes/otool -I libft -Weverything

clean:
	rm -rf objs

fclean: clean
	make -C libft fclean
	rm -f $(NM)
	rm -f $(TOOL)

re: fclean all
