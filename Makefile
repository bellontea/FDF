NAME	=   test
HEADER  =   header.h

SRCS_UTILS =   $(shell ls ./utils/*.c)

SRCS	=   ${SRCS_UTILS} main.c

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

CC		=   gcc

OBJS	=	$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME): 	$(OBJS) $(HEADER)
			$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) ${OBJS}

%.o: 		%.c
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
			$(RM) ${OBJS} ${BONUS_OBJS}

fclean:		clean
			$(RM) $(NAME) $(BONUS_NAME)

re:			fclean all

.PHONY: clean fclean re