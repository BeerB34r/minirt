SRC		=	get_fundamentals.c \
			parse_singleton.c \
			parse_trunk.c \
			parse_helpers.c \
			cleanup.c \
			minirt_parse.c \
			main.c \
			free_array.c \
			free_split_array.c \
			file_to_array.c \
			split_str_array.c \
			clean_split_array.c 
SRCDIR	=	src/utils/ src/ 
BIN		=	$(addprefix $(BINDIR),$(SRC:.c=.o))
BINDIR	=	bin/
DEP		=	$(addprefix $(DEPDIR),$(SRC:.c=.d))
DEPDIR	=	dep/
DEPFLAG	=	-MM -MF $@ -MT $@ -MT $(BINDIR)$(addsuffix .o,$(notdir $(basename $<)))
INC		=	-Ilib/libft/include -I inc -g3
VPATH	=	$(SRCDIR)
CFLAGS	=	-Wall -Wextra -Werror $(INC)
CC		=	cc
NAME	=	minirt_parser

.DEFAULT_GOAL	=	all
.PRECIOUS	: $(BINDIR) $(DEPDIR)

include	$(DEP)

all		:	$(NAME)

$(NAME)	:	$(BIN)
	$(CC) $(CFLAGS) -o $@ $^ lib/libft/libft.a

$(DEPDIR)%.d	:	%.c | $(DEPDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAG) $<
$(BINDIR)%.o	:	%.c	| $(BINDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

%/	:
	mkdir -p $@

clean	:
	$(RM) -r $(BINDIR)

fclean	:
	$(RM) -r $(BINDIR)
	$(RM) -r $(DEPDIR)
	$(RM) $(NAME)

re		:
	$(MAKE) fclean
	+$(MAKE) all

.PHONY	:	debug clean fclean re all
