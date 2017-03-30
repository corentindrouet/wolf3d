# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2017/03/30 09:15:18 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=wolf3d
CC= clang
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= main.c \
		  mlx_img_manager.c \
		  game.c \
		  raycasting.c \
		  raycasting2.c \
		  search_pt_segment.c \
		  event.c \
		  precalculing.c \
		  close_event.c \
		  read_bitmap.c \
		  check_map.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libftprintf.a
LIB_ID= ftprintf
LIB_PATH= ./libft/
LIB_INC= ./libft/
VERSION= $(shell sw_vers -productVersion | sed 's/\./ /g' | awk '{print$$2}')
ifeq ($(VERSION), 11)
  INFO= El Captain
  MLX_PATH= ./mlx/
  MLX_INC= ./mlx/
else
  INFO= Sierra
  MLX_PATH= ./mlx_sierra/
  MLX_INC= ./mlx_sierra/
endif
MLX_ID= mlx
MLX_NAME= libmlx.a
MLX_FLAG= -framework OpenGL -framework AppKit
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))
MLX= $(addprefix $(MLX_PATH), $(MLX_NAME))

$(NAME) : $(MLX) $(LIB) $(OBJ)
	$(info Compiling executable...)
	@$(CC) $(CFLAGS) -I$(INC_PATH) -o $(NAME) -L$(LIB_PATH) -l$(LIB_ID) -L$(MLX_PATH) -l$(MLX_ID) $(MLX_FLAG) $(OBJ)
	$(info Done !)

.PHONY: all
all: $(NAME)

$(LIB):
	$(info Compiling libft)
	@make -C $(LIB_PATH)
	@echo ""

$(MLX):
	$(info Compiling mlx for Mac OS X $(INFO))
	@make -C $(MLX_PATH)
	@echo ""

.PHONY: mlx
mlx:
	@make re -C $(MLX_PATH)

.PHONY: libft
libft:
	@make re -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@/bin/echo -n "Compiling $<..."
	@$(CC) -I$(INC_PATH) -I$(LIB_INC) -I$(MLX_INC) $(CFLAGS) -o $@ -c $<
	@echo "Done !"

.PHONY: clean
clean:
	$(info Delete binaries)
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	$(info Done !)
	@echo ""
	$(info Delete libft Binaries)
	@make $@ -C $(LIB_PATH)
	@echo ""
	$(info Delete mlx Binaries)
	@make $@ -C $(MLX_PATH)
	@echo ""

.PHONY: fclean
fclean: clean
	$(info Delete executable)
	@rm -f $(NAME)
	$(info done !)
	@echo ""
	$(info Delete libft executable)
	@make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
