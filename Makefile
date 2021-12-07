NAME = philo
INCLUDES = -I$(HEADERS_DIRECTORY)

# Header files
HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = philosophers.h philosophers_bonus.h #errors.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

# Sources
SRC_DIRECTORY = ./philo_sources/
SRC_BONUS_DIRECTORY = ./philo_bonus_sources/
SRC_LIST = main.c init.c utils.c ft_atoi.c
# SRC_BONUS_LIST = main.c init.c utils.c ft_atoi.c
SRCS = $(addprefix $(SRC_DIRECTORY), $(SRC_LIST))
# SRCS_BONUS = $(addprefix $(SRC_BONUS_DIRECTORY), $(SRC_BONUS_LIST))

# Objects
OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# Utils
CC = gcc
FLAGS = -Wall -Wextra -Werror

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS) Makefile
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o: $(SRC_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all
