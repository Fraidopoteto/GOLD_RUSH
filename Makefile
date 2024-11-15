# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Furaido <Furaido@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 14:22:55 by joschmun          #+#    #+#              #
#    Updated: 2024/11/15 13:52:10 by Furaido          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name des ausführbaren Programms
NAME = so_long

# Compiler und Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Quell- und Objektdateien
SRCS = main.c get_next_line.c read_map.c enemy00.c enemy01.c player00.c \
		render_map.c validate_map.c # Weitere Quell-Dateien können hier hinzugefügt werden
OBJS = $(SRCS:.c=.o)

# Pfad zu libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)

# Pfad zu MiniLibX
MLX_DIR = ./minilibx-linux  # Ersetze dies durch den tatsächlichen Pfad zu MiniLibX
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext  # Anpassung für Linux
# Falls du auf macOS bist, nutze stattdessen: MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Regeln
all: $(LIBFT) $(NAME)

# Erstellen des ausführbaren Programms
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

# Kompilieren der libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Erstellen der Objektdateien
%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_INC) -I$(MLX_DIR) -c $< -o $@

# Aufräumen der Objektdateien
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

# Aufräumen der Objektdateien und der ausführbaren Datei
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Alles neu erstellen
re: fclean all

.PHONY: all clean fclean re
