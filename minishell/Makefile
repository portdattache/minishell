# === CONFIGURATION ===
NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I includes/ -g3

# === COULEURS ===
RESET       = \033[0m
GREEN       = \033[32m
RED         = \033[31m
YELLOW      = \033[33m

# === RÉPERTOIRES ===
SRC_DIR     = src/
OBJ_DIR     = obj/
LIB_DIR = lib
LIB_A   = $(LIB_DIR)/libft.a

# === SOURCES ===
SRC         = \
	src/add_arg_redir.c \
	src/builtin_cd.c \
	src/builtin_echo.c \
	src/builtin_env.c \
	src/builtin_exit.c \
	src/builtin_export.c \
	src/builtin_pwd.c \
	src/builtin_unset.c \
	src/env_to_array.c \
	src/executables.c \
	src/execution.c \
	src/execution_utils.c \
	src/export_utils.c \
	src/get_cmd.c \
	src/is_builtin.c \
	src/lexer.c \
	src/lexer_util.c \
	src/main.c \
	src/parser.c \
	src/parse_token.c \
	src/path_finder.c \
	src/path_utils.c \
	src/pipe_error.c \
	src/pipe_exec.c \
	src/pipe_here_doc.c \
	src/pipe_infile_manager.c \
	src/pipe_outfile_manager.c \
	src/pipe_redirection.c \
	src/print_errors.c \
	src/quote_gestion.c \
	src/quote_gestion_utils.c \
	src/signals.c \
	src/structure_free_2.c \
	src/structure_free.c \
	src/structure_init.c \
	src/utils.c \
	src/utils_checker.c
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

$(NAME): $(OBJ) | $(LIB_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_A) -o $(NAME) -lreadline
	@echo "\n$(RESET)✅ Compilation terminée : $(NAME)$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(update_progress)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIB_A):
	@$(MAKE) -sC $(LIB_DIR)

update:
	@bash -c '\
		IGNORED_DIRS=("build" "test"); \
		FIND_CMD="find src -type f -name '\''*.c'\''"; \
		for dir in "$${IGNORED_DIRS[@]}"; do \
			FIND_CMD+=" ! -path '\''src/$$dir/*'\''"; \
		done; \
		SOURCE_LIST=$$(eval "$$FIND_CMD" | sort); \
		eval "$$FIND_CMD" | sort | awk '\''{print "\t" $$0 " \\"}'\'' \
		| sed '\''$$ s/ \\$$//'\'' > .sources_block; \
		echo "SRC         = \\" > .sources_full; \
		cat .sources_block >> .sources_full; \
		awk '\'' \
			FNR==NR { lines[NR] = $$0; next } \
			/^SRC[[:space:]]*=/{ \
				for (i=1; i<=length(lines); i++) print lines[i]; \
				in_block=1; next \
			} \
			in_block && /^[^[:space:]]/ { in_block=0 } \
			!in_block { print } \
		'\'' .sources_full Makefile > Makefile.tmp; \
		mv Makefile.tmp Makefile; \
		rm -f .sources_block .sources_full; \
		echo "✅ Makefile mis à jour avec les fichiers sources"; \
	'

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
