NAME = fdf

LIBRARIES = -lmlx -lm -lft -L$(LIBFT_DIRECTORY) -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit 
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(MINILIBX_HEADERS)

# Headers
HEADERS_DIRECTORY = -I./includes/
HEADERS = $(shell ls ./includes/*.h)

# Minilibx
MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./minilibx/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

# Libft_gnl
LIBFT = $(LIBFT_DIRECTORY)libft_gnl.a
LIBFT_DIRECTORY = ./libft_gnl/
LIBFT_HEADERS = ./libft_gnl/includes/

# Sources
SOURCES_DIRECTORY = ./sources/
SOURCES = $(shell ls ./sources/*.c)

# OBJS files
OBJS = $(SOURCES:%.c=%.o)
OBJS_MINILIBX = $(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

# Compilation
CC = gcc
C_FLAGS = -Wall -Wextra -Werror -O3

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Utils
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)


$(NAME): $(LIBFT) $(MINILIBX) $(OBJS) Makefile
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

%.o: %.c
	$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@
# $(OBJECTS_LIB)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
# 	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
# 	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@$(RM) -rf $(OBJS)
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(MINILIBX)
	@echo "$(NAME): $(RED)$(MINILIBX) was deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all