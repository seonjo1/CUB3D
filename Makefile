# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 21:01:14 by michang           #+#    #+#              #
#    Updated: 2024/02/04 16:29:40 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
WFLAG		:= -Wall -Wextra -Werror
LIBMLX		:= -L./ -lmlx -framework OpenGL -framework Appkit -lz
LIBFT		:= -Llibft -lft
MLX			:= ./libmlx.dylib
FT			:= ./libft/libft.a

DIR			:= ./
BASE		:=	main
				gnl/gnl	gnl/get_next_line gnl/get_next_line_utils
SRC			:= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			:= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		:= cub3d

# BON_DIR		:= ./bon/
# BON_BASE	:= 
# BON_SRC		:= $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(BON_BASE)))
# BON_OBJ		:= $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(BON_BASE)))
# BON_NAME	:= minishell

all : $(NAME)

$(NAME): $(OBJ) $(MLX) $(FT)
	$(CC) $(LIBMLX) $(LIBFT) $< -o $@

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
	@make fclean -C ./libft
	@make fclean -C ./minilibx
	rm -f $(NAME) $(BON_NAME)

re : fclean all

t : all clean
	./$(NAME)

.PHONY : all clean fclean re t
