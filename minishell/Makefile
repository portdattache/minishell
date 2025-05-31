# === CONFIGURATION ===
NAME        = minishell
CC          = clang
CFLAGS      = -Wall -Wextra -Werror -I includes/ -g3

# === COULEURS ===
RESET       = \033[0m
GREEN       = \033[32m
RED         = \033[31m
YELLOW      = \033[33m

# === RÉPERTOIRES ===
SRC_DIR     = src/
OBJ_DIR     = obj/
OCTOLIB_DIR = octolib
OCTOLIB_A   = $(OCTOLIB_DIR)/libft.a

# === SOURCES ===
SRC         = src/find_cmd_path.c\
			  src/ft_cd.c\
			  src/structure_init.c\
			  src/structure_free.c\
			  src/structure_free_2.c\
			  src/utils.c\
			  src/print_error.c\
			  src/ft_echo.c\
			  src/ft_env.c\
			  src/ft_exec.c\
			  src/ft_exec_1.c\
			  src/ft_exec_2.c\
   			  src/ft_exec_utils_1.c\
			  src/ft_executables.c\
			  src/ft_exit.c\
			  src/ft_export_utils_1.c\
			  src/ft_export.c\
			  src/ft_here_doc.c\
			  src/ft_lexer_utils_1.c\
			  src/ft_lexer_utils_2.c\
			  src/ft_lexer.c\
			  src/ft_parce_util_1.c\
			  src/ft_parce_util_2.c\
			  src/ft_parse_1.c\
			  src/ft_parse.c\
			  src/ft_pipe_manage_infile.c\
			  src/ft_pipe_manage_outfile.c\
			  src/ft_pipe_1.c\
			  src/ft_pipe.c\
			  src/ft_pwd.c\
			  src/ft_quote_utils_1.c\
			  src/ft_quote.c\
			  src/main.c\
			  src/signal.c\
			  src/tranform_in_tab.c\
			  src/ft_unset.c\

OBJ         = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# === PROGRESS BAR ===
TOTAL_FILES = $(words $(SRC))
COMPILED    = 0

define update_progress
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@printf "\r$(RED)Compiling [%-50s] %d%% (%d/%d)$(RESET)" \
		"$$(printf '█%.0s' $$(seq 1 $$(($(COMPILED)*50/$(TOTAL_FILES)))))" \
		$$(($(COMPILED)*100/$(TOTAL_FILES))) \
		$(COMPILED) \
		$(TOTAL_FILES)
endef

# === RÈGLES ===

all: $(NAME)

$(NAME): $(OBJ) | $(OCTOLIB_A)
	@$(CC) $(CFLAGS) $(OBJ) $(OCTOLIB_A) -o $(NAME) -lreadline
	@echo "\n$(RESET)✅ Compilation terminée : $(NAME)$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(update_progress)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OCTOLIB_A):
	@$(MAKE) -sC $(OCTOLIB_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -sC $(OCTOLIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(OCTOLIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re