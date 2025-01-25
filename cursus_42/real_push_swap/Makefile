# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 13:46:37 by bcaumont          #+#    #+#              #
#    Updated: 2025/01/25 09:54:51 by bcaumont         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC = main.c \
	  algorythms.c \
	  checkers.c \
	  double_linked_list.c \
	  errors.c \
	  finders.c \
	  init_nodes.c \
	  moves.c \
	  push.c \
	  rev_rotates.c \
	  rotates.c \
	  sets.c \
	  swaps.c \
	  utils.c

OBJS = $(SRC:.c=.o)

LIB_DIR = libft
LIB_A = $(LIB_DIR)/libft.a

PRINT_DIR = ft_printf
PRINT_A = $(PRINT_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIB_DIR) bonus
	@$(MAKE) -C $(PRINT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_A) $(PRINT_A) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(PRINT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(MAKE) -C $(PRINT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re