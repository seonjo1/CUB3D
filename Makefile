# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 21:01:14 by michang           #+#    #+#              #
#    Updated: 2024/01/31 18:28:03 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
WFLAG		:= -Wall -Wextra -Werror
MLX			:= -L. -lmlx -framework OpenGL -framework AppKit -lz
LIBFT		:= -Llibft -lft

DIR			:= ./
BASE		:= main
SRC			:= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			:= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		:= cub3d

# BON_DIR		:= ./bon/
# BON_BASE	:= 
# BON_SRC		:= $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(BON_BASE)))
# BON_OBJ		:= $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(BON_BASE)))
# BON_NAME	:= minishell

all : $(NAME)

$(NAME) : $(OBJ)
	@make lib
	$(CC) -I$(dir $<) $(MLX) $(LIBFT) $^ -o $@

# bonus : $(BON_OBJ)
# 	@make lib
# 	$(CC) -I$(dir $<) $(LIBFT) $(READLINE) $^ -o $(BON_NAME)
# 	@touch bonus

%.o : %.c
	$(CC) $(WFLAG) -I$(dir $<) -c $< -o $@

lib :
	@make re -j -C ./libft

clean :
	make clean -C ./libft
	rm -f $(OBJ) $(BON_OBJ) bonus

fclean : clean
	rm -f $(NAME) $(BON_NAME) ./libft/libft.a

re : clean all

.PHONY : all clean fclean re lib
