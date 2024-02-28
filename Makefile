# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 21:01:14 by michang           #+#    #+#              #
#    Updated: 2024/02/28 20:59:04 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	cc
WFLAG		:=	-Wall -Wextra -Werror -O3
MLXFLAG		:=	-L./ -lmlx -framework OpenGL -framework Appkit -lz
FTFLAG		:=	-Llibft -lft
MLX			:=	./libmlx.dylib
BASSFLAG	:=	-Lbass -lbass
FT			:=	./libft/libft.a

DIR			:=	./src/
BASE		:=	main \
				gnl/gnl	gnl/get_next_line gnl/get_next_line_utils \
				parse/parse parse/parse_check_map parse/parse_make_map \
				parse/parse_sizing_map parse/parse_utils \
				parse/parse_tex parse/parse_tex_color parse/parse_tex_file \
				rc/rc_get_distance rc/rc_raycast \
				play/play play/play_action play/play_dir \
				play/play_state \
				evnt/evnt evnt/evnt_utils evnt/evnt_kb_set \
				libft_s/libft_s libft_s/vec2_utils libft_s/utils \
				obj/obj_minimap
SRC			:= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			:= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		:= cub3D

BON_DIR		:= ./bon/
BON_BASE	:= 	$(filter-out parse_tex_color, $(BASE)) \
				rc/rc_draw_floor rc/rc_thread rc/rc_draw_sky \
				play/play_recall\
				hand/hand hand/hand_action hand/hand_shot \
				sound/sound sound/sound_utils
BON_SRC		:= $(addprefix $(BON_DIR), $(addsuffix .c, $(BON_BASE)))
BON_OBJ		:= $(addprefix $(BON_DIR), $(addsuffix .o, $(BON_BASE)))
BON_NAME	:= cub3D

all : $(NAME)

$(NAME): $(OBJ) $(MLX) $(FT)
	$(CC) $(WFLAG) $(MLXFLAG) $(FTFLAG) $^ -o $@

bonus : $(BON_OBJ) $(MLX) $(FT)
	$(CC) $(WFLAG) $(MLXFLAG) $(FTFLAG) $(BASSFLAG) $^ -o $(BON_NAME)
	install_name_tool -change @loader_path/libbass.dylib @loader_path/bass/libbass.dylib $(BON_NAME)
	@touch bonus

$(MLX) :
	@if [ ! -f $(MLX) ]; then make -C ./minilibx; fi

$(FT) :
	@if [ ! -f $(FT) ]; then make -j -C ./libft; fi

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

.PHONY : all clean fclean re
