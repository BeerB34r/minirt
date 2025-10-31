SRC				!=	cat src.list
SRCDIR			=	src/ \
					src/utils/ \
					src/parsing/ \
					src/mlx/ \
					src/math/ \
					src/math/intersection/ \
					src/math/superquadric \
					src/math/superquadric/ellipsoid/ \
					src/math/superquadric/hyperboloid1 \
					src/math/superquadric/hyperboloid2 \
					src/math/superquadric/toroid \

TESTDIR			=	test/
TESTFLAGS		=	-g3
BIN				=	$(addprefix $(BINDIR),$(SRC:.c=.o))
BINDIR			=	bin/
DEP				=	$(addprefix $(DEPDIR),$(SRC:.c=.d))
DEPDIR			=	dep/
DEPFLAG			=	-MM -MF $@ -MT $@ -MT $(BINDIR)$(addsuffix .o,$(notdir $(basename $<)))
INC				=	-Ilib/libft/include -Iinc -Ilib/mlx42/include/MLX42
VPATH			=	$(SRCDIR)
CFLAGS			:=	-Wall -Wextra -Werror -ffast-math -O3 -fhonor-infinities -fhonor-nans
CPPFLAGS		=	$(INC) -g3
LDFLAGS			=	-lm lib/libft/libft.a lib/mlx42/build/libmlx42.a -ldl -lglfw -pthread
CC				:=	cc
NAME			:=	minirt_parser

MAKEFLAGS		+=	-r
.EXTRA_PREREQS	=	$(firstword $(MAKEFILE_LIST))
.DEFAULT_GOAL	=	all
.PRECIOUS		:	$(BINDIR) $(DEPDIR)
.PHONY			:	debug clean fclean re all

-include	$(DEP)

all				:	$(NAME)

$(NAME)			:	$(BIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(DEPDIR)%.d	:	%.c | $(DEPDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAG) $<
$(BINDIR)%.o	:	%.c	| $(BINDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

test_%			:	%.o
	$(CC) $(CPPFLAGS) $(TESTFLAGS) -o $@ $< $(TESTDIR)$(basename $<).c $(LDFLAGS)
	./$@

%/				:
	@mkdir -p $@

clean			:
	$(RM) -r $(BINDIR)

fclean			:
	$(RM) -r $(BINDIR)
	$(RM) -r $(DEPDIR)
	$(RM) $(NAME)

re				:
	$(MAKE) fclean
	+$(MAKE) all
