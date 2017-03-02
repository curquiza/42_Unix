# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: curquiza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/16 17:08:05 by curquiza          #+#    #+#              #
#    Updated: 2017/02/20 12:33:53 by curquiza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc -Wall -Wextra -Werror

INCL_FLAG = -I includes -I $(LIB_DIR)/includes

DIR_SRC = srcs
SRC = $(addprefix $(DIR_SRC)/, \
	  functions.c \
	  sort_ascii.c \
	  options.c \
	  create_structpath.c \
	  start.c \
	  opt_t.c \
	  opt_r.c \
	  opt_bigr.c \
	  opt_l.c \
	  opt_f.c \
	  opt_bigs.c \
	  opt_d.c \
	  opt_u.c \
	  opt_bigu.c \
	  opt_bigt.c \
	  fcttab.c \
	  infodir_1.c \
	  infodir_2.c \
	  display.c \
	  display_indir.c \
	  display_notdir.c \
	  acl_xattr.c \
	  color.c \
	  column.c \
	  main.c)

DIR_OBJ = objs
OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

LIB = $(LIB_DIR)/libft.a
LIB_DIR = libft
LIB_FLAG = -L$(LIB_DIR) -lft

all : $(NAME)

$(LIB) :
	@make -C $(LIB_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@" "OK"
	@echo "\033[1;31m-- OBJECTS ---------------------\033[0m"

$(NAME) : $(LIB) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIB_FLAG)
	@echo "\033[1;31m-- EXEC ------------------------\033[0m"
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) -o $@ -c $< $(INCL_FLAG)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@make clean -C $(LIB_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@_libft" "OK"
	@rm -f $(OBJ)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

fclean : clean
	@make fclean -C $(LIB_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@_libft" "OK"
	@rm -f $(NAME)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

re : fclean all
