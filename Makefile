# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amugisha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 23:35:13 by amugisha          #+#    #+#              #
#    Updated: 2025/01/15 17:43:56 by amugisha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all $(LIB) clean fclean re

GREEN='\033[0;32m'

RED='\033[0;31m'

BRUN='\033[0;33m'


NAME = fractol

CC = cc

HEADERM = mlx/mlx.h
HEADER =  header.h
LIB = libfractol.a
SRC = ft_strncmp.c fractal.c events.c set_up.c \
       verification.c utils.c color.c zoom.c \
       error.c color_d.c dragon.c fractal_bis.c \
	   animation.c
	   
OBJ = $(SRC:.c=.o)
OBJM = $(MAIN:.c=.o)
CFLAGS = -Wall -Wextra -Werror -I $(HEADERM) -I $(HEADER) -g3 -O3
MLX_PATH = mlx/
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)
MAIN = main.c

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(MLX) $(LIB) $(OBJM) $(HEADER)
	@echo $(BRUN) "Compiling fractol..."
	@$(CC) $(CFLAGS) $(OBJM) $(LIB) -Lmlx -lmlx -L/usr/lib/x86-64-linux-gnu -lXext -lX11 -lm -lz -o $(NAME)
	@echo $(GREEN) "OK : Compile fractol"

$(LIB): $(OBJ)
	@ar rcs -o $(LIB) $(OBJ)

$(MLX):
	@echo $(BRUN) "Making MiniLibX..."
	@make -sC $(MLX_PATH)
	@echo $(GREEN) "OK : Make MiniLibX"

bonus: all	 

all: $(NAME)

clean:
	@echo $(BRUN) "Removing .o object files..."
	@rm -rf $(OBJ) $(OBJM) Makefile.gen
	@echo $(GREEN) "OK :Remove .o object files"

fclean: clean
	@make clean -C $(MLX_PATH)
	@echo $(BRUN) "Removing fractol..."
	@rm -rf $(NAME) $(LIB)
	@echo $(GREEN) "OK :Remove fractol"

re: fclean all	
