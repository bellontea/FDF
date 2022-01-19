NAME = fdf

INC=/usr/X11/include
INCLIB=$(INC)/../lib

LIBRARIES =  -lmlx -lm -L$(MINILIBX_DIRECTORY) -L$(LIBFT_DIRECTORY)  -framework OpenGL -framework AppKit -L$(INCLIB) -lXext -lX11 -lm
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(MINILIBX_HEADERS) -I$(LIBFT_HEADERS)

# Header files
HEADERS_DIRECTORY = ./includes/
HEADERS = $(shell ls ./includes/*.h)

# MINILIBX
MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./mlx/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

# Libft
LIBFT = $(LIBFT_DIRECTORY)libft_gnl.a
LIBFT_DIRECTORY = ./libft_gnl/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)/includes/

# Sources
SOURCES = $(shell ls ./sources/*.c)

# OBJS files
OBJECTS_DIRECTORY = objects/
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(SOURCES:.c=.o)) $(LIBFT)
# Utils
CC = gcc
FLAGS = -Wall -Wextra -Werror -o3
# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
.PHONY: all clean fclean re bonus
all: $(NAME)
$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS) Makefile
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"
$(OBJECTS_DIRECTORY)%.o :%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c 	$(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"
$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)
$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)
clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
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

bonus: all