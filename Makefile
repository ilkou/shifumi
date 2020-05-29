# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oouklich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/14 01:58:23 by oouklich          #+#    #+#              #
#    Updated: 2020/05/29 14:16:33 by oouklich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = shifumi

SRCS = main.c init.c image.c component.c quit.c events.c socketClient.c load_components.c display.c
SRCS += mx/mixer.c\
       mx/mixer_events.c\
       mx/mixer_tools.c
SRCS += libft/ft_strjoin.c\
	libft/ft_itoa.c
SRC_DIR = src
SRC = $(SRCS:%.c=$(SRC_DIR)/%.c)

#OBJS = $(SRCS:mx/%=%)

OBJS = $(SRCS:.c=.o)
OBJ_DIR = obj
OBJ = $(OBJS:%.o=$(OBJ_DIR)/%.o)

INC_DIR = inc

ifeq ($(shell uname), Darwin)
$(info MacOs detected)
MLX_DIR = minilibx_macos
MLX_FLAGS = -I $(MLX_DIR) $(MLX_DIR)/libmlx.dylib -framework OpenGL -framework AppKit
SDL2_DIR = ./frameworks
SDL2 = $(SDL2_DIR)/SDL2.framework/Versions/A/SDL2
SDL2_MIXER = .$(SDL2_DIR)/SDL2_mixer.framework/Versions/A/SDL2_mixer
SDL2_FLAGS = -I $(INC_DIR)/SDL2 -F $(SDL2_DIR) -framework SDL2 -framework SDL2_MIXER
else
$(info $(shell uname) detected)
MLX_DIR = minilibx_linux
MLX_FLAGS = -I $(MLX_DIR) -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
SDL2_FLAGS = 
endif

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	make -C $(MLX_DIR)
	gcc -o $(NAME) $(OBJ) -I $(INC_DIR) -lpthread $(MLX_FLAGS) $(SDL2_FLAGS)

ifeq ($(shell uname), Darwin)
	@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(NAME)
	@install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer $(SDL2_MIXER) $(NAME)
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -o $@ -c $< -I $(INC_DIR) -I $(INC_DIR)/SDL2

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/mx
	@mkdir -p $(OBJ_DIR)/libft

clean:
	make clean -C $(MLX_DIR)
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
