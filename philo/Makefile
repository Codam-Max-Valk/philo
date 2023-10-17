NAME := philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
HEADER = include/philo.h
INCLUDE = -Iinclude
OBJ_DIR = obj
SRCFILES = 	main \
			process_input \
			philo \
			utils \
			philo_actions \
			init_philo \

vpath %.c	src	src/utils
_SRC = $(addsuffix .c, $(SRCFILES))
OBJFILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(_SRC))

# Color definitions

GREEN = \033[0;92m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
BLUE = \033[0;94m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(OBJFILES)
	@echo "$(BLUE)compiling $(NAME) $(COLOR_END)"
	@$(CC) $(CFLAGS) $(OBJFILES) $(INCLUDE) -o $(NAME)
	@echo "$(GREEN)compilation complete!$(COLOR_END)"
	
$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJFILES)
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)clean complete!$(COLOR_END)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re 

