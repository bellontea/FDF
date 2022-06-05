NAME		=	fdf

LIBFT		=	./libft_gnl/libft_gnl.a
PATH_HEADER =	./includes/
PATH_LIB 	=	./libft_gnl/
OBJ_DIR		=	./objects
HEADER  	=	./includes/fdf.h

INC			=	/usr/include
INCLIB		=	$(INC)/../lib

SRC		=	$(shell ls ./sources/*.c)
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o)) $(LIBFT)

CFLAGS		=	-o3 -I$(PATH_HEADER) -Imlx -I$(INC) -Wall -Wextra -Werror 
LFLAGS		=	-L./mlx -lmlx -L$(INCLIB) -lXext -lX11 -lm 
RM			=	rm -rf
CC			=	gcc

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	INC		=	/usr/X11/include
endif

all:		run_libft $(NAME) 

$(NAME):	$(OBJ)
			$(CC) -o $(NAME) ${OBJ} $(LFLAGS) 

run_libft:	
			@make -sC ./mlx
			@make -sC $(PATH_LIB)

$(OBJ_DIR)/%.o: %.c $(PATH_HEADER)*
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) ${OBJ_DIR}
			@make -sC ./mlx clean
			@make -sC $(PATH_LIB) clean

fclean:		clean
			@$(RM) $(NAME)
			@make -sC $(PATH_LIB) fclean

re:			fclean all

.PHONY: clean fclean re all