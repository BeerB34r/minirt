SRC		=	minirt_parse.c
OBJ		=	$(SRC:.c=.o)
INC		=	-Ilib/libft/include
CFLAGS	=	-Wall -Wextra -Werror $(INC)
CC		=	cc
NAME	=	minirt_parser

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ lib/libft/libft.a
