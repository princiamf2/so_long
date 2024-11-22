# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mm-furi <mm-furi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 16:34:36 by mm-furi           #+#    #+#              #
#    Updated: 2024/11/18 16:59:54 by mm-furi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -Imlx
LIBFT = libft/libft.a
SRC = bfs.c check.c draw.c enemy.c frame.c free.c get_next_line.c \
     get_next_line_utils.c get_next_line_utils2.c handle.c init.c \
     init2.c input.c load_tilesheet.c load.c main.c map.c move_enemies.c \
     read_map.c sprite.c tiles.c valide_map.c game_over.c map2.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

# Compilation des fichiers .c vers obj/*.o
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Création du dossier obj si nécessaire
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

debug: $(OBJ)
	$(CC) $(CFLAGS) -fsanitize=address -g $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
