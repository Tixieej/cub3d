# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rde-vrie <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/13 10:40:20 by rde-vrie      #+#    #+#                  #
#    Updated: 2020/07/30 16:42:28 by rde-vrie      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = raycast.c raycast_2.c textures.c cubed.c keys.c key_release.c start.c \
	get_next_line.c get_next_line_utils.c ft_strcmp.c screenshot.c error.c  \
	import_textures.c floodfill.c map.c map_2.c map_3.c map_4.c map_5.c \
	sort_sprites.c sprites.c atoi_colour.c
OBJ = $(addprefix objs/, $(SRC:.c=.o))
CFLAGS = -Wall -Werror -Wextra
CC = gcc
MLXFOLDER = mlx_beta
MLX = libmlx.dylib
LIBFT = libft.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) -L. -lmlx -lft -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)

test: $(NAME)
	./$(NAME)

$(MLX):
	cd $(MLXFOLDER) && make
	mv $(MLXFOLDER)/$(MLX) .

$(LIBFT):
	cd libft && make
	mv libft/$(LIBFT) .

objs/%.o: srcs/%.c cub3d.h
	mkdir -p objs
	gcc $(CFLAGS) -I$(MLXFOLDER) -Ilibft -I. -c $< -o $@

clean:
	$(RM) $(OBJ)
	cd libft && make clean
	cd $(MLXFOLDER) && make clean

fclean:	clean
	$(RM) $(NAME)
	rm -rf $(LIBFT)
	$(RM) $(MLX)

re: fclean all
