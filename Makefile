NAME = philo
NAME_BONUS = philo_bonus
INCLUDES = -I$(HEADERS_DIRECTORY)

# Header files
HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = philosophers.h philosophers_bonus.h errors.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

# Sources
SRC_DIRECTORY = ./philo_sources/
SRC_DIRECTORY_BONUS = ./philo_bonus_sources/
SRC_LIST = events.c finish.c ft_atoi.c init.c main.c \
			processing.c utils_libft.c utils_philo.c \
			message.c
SRC_BONUS_LIST = events.c ft_atoi.c init.c main.c \
			processing.c utils_libft.c utils_philo.c \
			message.c
SRCS = $(addprefix $(SRC_DIRECTORY), $(SRC_LIST))
SRCS_BONUS = $(addprefix $(SRC_DIRECTORY_BONUS), $(SRC_BONUS_LIST))

# Objects
OBJECTS_DIRECTORY = objects/
OBJECTS_DIRECTORY_BONUS = objects_bonus/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJECTS_BONUS_LIST = $(patsubst %.c, %.o, $(SRC_BONUS_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))
OBJECTS_BONUS = $(addprefix $(OBJECTS_DIRECTORY_BONUS), $(OBJECTS_BONUS_LIST))

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

bonus: $(OBJECTS_DIRECTORY_BONUS) $(OBJECTS_BONUS) Makefile
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS_BONUS) -o $(NAME_BONUS)
	@echo "\n$(NAME_BONUS): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME_BONUS): $(GREEN)$(NAME_BONUS) was created$(RESET)"

$(OBJECTS_DIRECTORY_BONUS):
	@mkdir -p $(OBJECTS_DIRECTORY_BONUS)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY_BONUS) was created$(RESET)"

$(OBJECTS_DIRECTORY_BONUS)%.o: $(SRC_DIRECTORY_BONUS)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	@rm -rf $(OBJECTS_DIRECTORY_BONUS)
	@echo "$(NAME_BONUS): $(RED)$(OBJECTS_DIRECTORY_BONUS) was deleted$(RESET)"
	@echo "$(NAME_BONUS): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@rm -f $(NAME_BONUS)
	@echo "$(NAME_BONUS): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all
