NAME	=   test
HEADER  =   ./header.h

# SRCS_UTILS =   $(shell ls ./utils/*.c)

SRCS	=    main.c

CFLAGS	= -Wall -Wextra -Werror

LFLAGS	=	-L./mlx -lmlx -framework OpenGL -framework AppKit

RM		= rm -rf

CC		=   gcc

OBJS	=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) ${LFLAGS} ${OBJS} -o $(NAME)

%.o: 		%.c $(HEADER)
			$(CC) $(CFLAGS) -I$(HEADER) -Imlx -c $< -o $@

clean:
			$(RM) ${OBJS}

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: clean fclean re