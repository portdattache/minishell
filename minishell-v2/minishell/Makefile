NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
SRC = src_built_in/cd.c\
	  src_built_in/echo.c\
	  src_built_in/env.c\
	  src_built_in/execute_builtin.c\
	  src_built_in/exit.c\
	  src_built_in/export.c\
	  src_built_in/pwd.c\
	  src_built_in/unset.c\
	  pipex/free.c\
	  pipex/init_pipex.c\
	  pipex/execution.c\
	  pipex/process.c\
	  pipex/path.c\
	  pipex/secure.c\
	  pipex/pipeline.c\
	  main/execute_pipe_from_minishell.c\
	  main/init_shell.c\
	  main/main.c\

OBJS = $(SRC:.c=.o)
LIB_DIR = lib
LIB_A = $(LIB_DIR)/libft.a

TOTAL_FILES = $(words $(SRC))
COMPILED    = 0

define update_progress
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
    @printf "\r$(YELLOW)Compiling [%-50s] %d%% (%d/%d)$(RESET)" \
        "$$(printf '█%.0s' $$(seq 1 $$(($(COMPILED)*50/$(TOTAL_FILES)))))" \
        $$(($(COMPILED)*100/$(TOTAL_FILES))) \
        $(COMPILED) \
        $(TOTAL_FILES)
endef

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC $(LIB_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_A) -o $(NAME) -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(update_progress)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIB_DIR) fclean

re: fclean all


.PHONY: all clean fclean re rec
