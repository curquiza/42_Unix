# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: curquiza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/16 17:08:05 by curquiza          #+#    #+#              #
#    Updated: 2017/05/15 16:19:41 by curquiza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc -g -Wall -Wextra -Werror
#CC = gcc -Wall -Wextra -Werror -fsanitize=address

INCL_FLAG = -I includes -I $(LIBFT_DIR)/includes

DIR_SRC = srcs
SRC = $(addprefix $(DIR_SRC)/, \
	  var_tab.c \
	  lex_list.c \
	  lexer.c \
	  lexer_token_type.c \
	  lexer_op_type.c \
	  parser.c \
	  syntax_error.c \
	  inhibitor.c \
	  inhibitor_check.c \
	  inhibitor_get_endoftoken.c \
	  here_doc.c \
	  ast.c \
	  expansion.c \
	  exp_quote_removal.c \
	  exp_parameter.c \
	  semantics.c \
	  sem_split.c \
	  sem_redir_list.c \
	  execution.c \
	  exec_error_msg.c \
	  exec_simple_cmd.c \
	  built_in.c \
	  main.c) 

DIR_OBJ = objs
OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = libft
LIBFT_FLAG = -L$(LIBFT_DIR) -lft

all : $(NAME)

$(LIBFT) :
	@echo "\033[1;31m-- LIBFT -----------------------\033[0m"
	@make -C $(LIBFT_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@" "OK"
	@echo "\033[1;31m-- OBJECTS ---------------------\033[0m"

$(NAME) : $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIBFT_FLAG) $(INCL_FLAG)
	@echo "\033[1;31m-- EXEC ------------------------\033[0m"
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) -o $@ -c $< $(INCL_FLAG)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@make clean -C $(LIBFT_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@_libft" "OK"
	@rm -f $(OBJ)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@printf  "%-45s\033[1;33m%s\033[0m\n" "Make $@_libft" "OK"
	@rm -f $(NAME)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

re : fclean all
