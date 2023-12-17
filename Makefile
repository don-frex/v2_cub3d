# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaber <asaber@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 19:29:52 by asaber            #+#    #+#              #
#    Updated: 2023/12/17 15:27:32 by asaber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:=  -Wunreachable-code -Ofast -Wextra -Wall -Werror -fsanitize=address -g
LIBMLX	:= /Users/$(USER)/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:=	cub3d.c draw.c put_pixel.c move.c player.c checks.c raycasting.c #raycasting.c
OBJS	:= ${SRCS:.c=.o} lib_functions/ft_split.o lib_functions/ft_strlen.o

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS)  -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx