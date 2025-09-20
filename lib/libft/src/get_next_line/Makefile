CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -Ofast
SRCS	=	get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS	=	$(SRCS:.c=.o)
INCL	=	$(INCLUDE)
NAME	=	$(LIBGNL)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
		ar -rcs $@ $?

%.o		:	%.c
		$(CC) $(CFLAGS) -o $@ -c $^ -I $(INCL)

fclean	:	clean
		rm -f $(NAME)

clean	:
		rm -f $(OBJS)

re		:	fclean all

.PHONY	:	fclean clean all re
