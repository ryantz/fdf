# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 08:56:45 by ryatan            #+#    #+#              #
#    Updated: 2026/02/10 13:06:39 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
COMPILER = cc
INCLUDES = -Iincludes -Ilibft -Ift_printf
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj
SRC_DIR = src

SRC = main.c \
	  push_swap_actions.c \
	  helpers.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
PRINTF_DIR = ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(COMPILER) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
