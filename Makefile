# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2017/03/21 11:42:45 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= wolf3d
CC= clang
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= main.c \
		  mlx_img_manager.c \
		  game.c \
		  raycasting.c \
		  search_pt_segment.c \
		  event.c \
		  precalculing.c \
		  close_event.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libft_printf.a
LIB_ID= ftprintf
LIB_PATH= ./libft/
LIB_INC= ./libft/
MLX_PATH= ./mlx/
MLX_INC= ./mlx/
MLX_ID= mlx
MLX_FLAG= -framework OpenGL -framework AppKit
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))
MLX= $(addprefix $(MLX_PATH), $(MLX_INC))

.PHONY: all
all: $(NAME)

$(NAME): $(MLX) $(LIB) $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_PATH) -o $(NAME)  -L$(LIB_PATH) -l$(LIB_ID) -L$(MLX_PATH) -l$(MLX_ID) $(MLX_FLAG) $(OBJ)

$(LIB):
	make -C $(LIB_PATH)

$(MLX):
	make -C $(MLX_PATH)

mlx:
	make re -C $(MLX_PATH)

.PHONY: libft
libft:
	make re -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) -I$(LIB_INC) -I$(MLX_INC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)
	make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	rm -fv $(NAME)
	make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
