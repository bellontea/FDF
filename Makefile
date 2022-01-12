NAME		=	fdf
LIBFT		=	./libft_gnl/libft_gnl.a
PATH_HEADER =	./includes/
LIBFT_HEADERS = ./libft_gnl/includes/
INCLUDES = -I$(PATH_HEADER) -I$(LIBFT_HEADERS)
PATH_LIB 	=	./libft_gnl/
HEADER  	=	./includes/fdf.h
INC			=	/usr/include
INCLIB		=	$(INC)/../lib

SOURCES	=	$(shell ls ./sources/*.c)

SRCS		=	$(SOURCES)
OBJS			=	$(SRCS:%.c=%.o) $(LIBFT)

CFLAGS		=	#-Wall -Wextra -Werror
LFLAGS		=	-L./mlx_linux -lmlx -L$(INCLIB) -lXext -lX11 -lm
RM			=	rm -rf
CC			=	gcc

all:		run_libft $(NAME) 

$(NAME):	${OBJS}
			$(CC) -o $(NAME) ${OBJS} $(LFLAGS) 

run_libft:	
			@make -C $(PATH_LIB)

%.o: 		%.c	
			$(CC) $(CFLAGS) $(INCLUDES) -Imlx_linux -I$(INC) -c $< -o $@

clean:
			$(RM) ${OBJS}
			@make -C $(PATH_LIB) clean
fclean:		clean
			$(RM) $(NAME)
			@make -C $(PATH_LIB) fclean
re:			fclean all
.PHONY: clean fclean re all
