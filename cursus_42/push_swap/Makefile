NAME = push_swap
NAME_BONUS = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = a_vers_b.c\
	  b_vers_a.c\
	  algo_3.c\
	  algo_turc.c\
	  main.c\
	  

SRC_BONUS = bonus/checker.c\
			bonus/get_next_line_checker.c\
			bonus/get_next_line_checker_utils.c\

SRC_UTILS = utils/poussee.c\
	    	utils/rotation_inversee.c\
	    	utils/rotation.c\
	  	    utils/swaps.c\
	  	    utils/erreurs.c\
			utils/chercheurs.c\
			utils/double_liste_chainee.c\
			utils/utils.c\
			utils/verifs.c\

OBJS_BONUS = $(SRC_BONUS:.c=.o)

OBJS = $(SRC:.c=.o)

OBJS_UTILS = $(SRC_UTILS:.c=.o)

LIB_DIR = libft
LIB_A = $(LIB_DIR)/libft.a

PRINT_DIR = ft_printf
PRINT_A = $(PRINT_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_UTILS)
	@$(MAKE) -sC $(LIB_DIR) all
	@$(MAKE) -sC $(PRINT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJS_UTILS) $(LIB_A) $(PRINT_A) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(OBJS_UTILS)
	@$(MAKE) -sC $(LIB_DIR) all
	@$(MAKE) -sC $(PRINT_DIR)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(OBJS_UTILS) $(LIB_A) $(PRINT_A) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_UTILS)
	@$(MAKE) -sC $(LIB_DIR) clean
	@$(MAKE) -sC $(PRINT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -sC $(LIB_DIR) fclean
	@$(MAKE) -sC $(PRINT_DIR) fclean

re: fclean all

re-bonus: fclean bonus

.PHONY: all bonus clean fclean re re-bonus
