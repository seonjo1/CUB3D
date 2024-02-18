# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 21:01:14 by michang           #+#    #+#              #
#    Updated: 2024/02/12 19:58:32 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
WFLAG		:= -Wall -Wextra -Werror #-fsanitize=address -g3
MLXFLAG		:= -L./ -lmlx -framework OpenGL -framework Appkit -lz
FTFLAG		:= -Llibft -lft
MLX			:= ./libmlx.dylib
FT			:= ./libft/libft.a

DIR			:= ./
BASE		:=	main \
				gnl/gnl	gnl/get_next_line gnl/get_next_line_utils \
				parse/parse parse/parse_check_map parse/parse_make_map \
				parse/parse_sizing_map parse/parse_utils \
				parse/parse_tex parse/parse_tex_color parse/parse_tex_file \
				rc/rc_get_distance rc/rc_raycast \
				play/play play/play_action play/play_recall \
				evnt/evnt evnt/evnt_utils \
				hand/hand \
				libft_s/libft_s libft_s/vec2_utils
SRC			:= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			:= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		:= cub3D

# BON_DIR	:= ./bon/
# BON_BASE	:= $(BASE)
# BON_SRC	:= $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(BON_BASE)))
# BON_OBJ	:= $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(BON_BASE)))
# BON_NAME	:= minishell

all : $(NAME)

$(NAME): $(OBJ) $(MLX) $(FT)
	$(CC) $(WFLAG) $(MLXFLAG) $(FTFLAG) $^ -o $@

$(MLX) :
	@if [ ! -f $(MLX) ]; then make -C ./minilibx; fi

$(FT) :
	@if [ ! -f $(FT) ]; then make -j -C ./libft; fi

# bonus : $(BON_OBJ)
# 	@make lib
# 	@make mlx
# 	$(CC) -I$(dir $<) $(LIBFT) $(READLINE) $^ -o $(BON_NAME)
# 	@touch bonus

%.o : %.c
	$(CC) $(WFLAG) -I$(dir $<) -c $< -o $@

clean :
	@make clean -C ./libft
	@make clean -C ./minilibx
	rm -f $(OBJ) $(BON_OBJ) bonus

fclean : clean
	# @make fclean -C ./libft
	# @make fclean -C ./minilibx
	rm -f $(NAME) $(BON_NAME)

re : fclean all

t1 : all clean
	./$(NAME) ./map/test_map.cub

t2 : all clean
	./$(NAME) ./map/test_map2.cub

t3 : all clean
	./$(NAME) ./map/test_map3.cub

t4 : all clean
	./$(NAME) ./map/test_map4.cub

t5 : all clean
	./$(NAME) ./map/test_map5.cub

norm :
	norminette evnt gnl libft libft_s map  parse play rc main.c

.PHONY : all clean fclean re t
