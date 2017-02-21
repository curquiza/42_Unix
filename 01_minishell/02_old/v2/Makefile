# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: curquiza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/16 17:08:05 by curquiza          #+#    #+#              #
#    Updated: 2017/02/04 17:25:04 by curquiza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Wextra -Werror

INCL_FLAG = -I includes -I $(LIB_DIR)/includes

DIR_SRC = srcs
SRC = $(addprefix $(DIR_SRC)/, \
	  functions.c \
	  commands_split.c \
	  get_arg.c \
	  parsing.c \
	  parsing_errors.c \
	  env.c \
	  builtin_echo.c \
	  builtin_env.c \
	  main.c)

DIR_OBJ = objs
OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

LIB = $(LIB_DIR)/libft.a
LIB_DIR = libft
LIB_FLAG = -L$(LIB_DIR) -lft

all : $(NAME)

$(LIB) :
	@make -C $(LIB_DIR)
	@echo "\033[1;31m--------------------------\033[0m"

$(NAME) : $(LIB) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIB_FLAG)
	@echo "\033[1;31m--------------------------\033[0m"
	@echo "Make $@ : \033[1;32mOK\033[0m"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) -o $@ -c $< $(INCL_FLAG)
	@echo "Make $@ : \033[1;32mOK\033[0m"

clean :
	@make clean -C $(LIB_DIR)
	@echo "Make $@_libft : \033[1;33mOK\033[0m"
	@rm -f $(OBJ)
	@echo "Make $@ : \033[1;32mOK\033[0m"

fclean : clean
	@make fclean -C $(LIB_DIR)
	@echo "Make $@_libft : \033[1;33mOK\033[0m"
	@rm -f $(NAME)
	@echo "Make $@ : \033[1;32mOK\033[0m"

re : fclean all
