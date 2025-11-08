SRC				!=	cat src.list
SRCDIR			:=	src/ \
					src/utils/ \
					src/parsing/ \
					src/mlx/ \
					src/mlx/modes/ \
					src/math/ \
					src/math/intersection/ \
					src/math/superquadric \
					src/math/superquadric/ellipsoid/ \
					src/math/superquadric/hyperboloid1 \
					src/math/superquadric/hyperboloid2 \
					src/math/superquadric/toroid \

TESTDIR			:=	test/
TESTFLAGS		:=	-g3
BIN				=	$(addprefix $(BINDIR),$(SRC:.c=.o))
BINDIR			:=	bin/
DEP				=	$(addprefix $(DEPDIR),$(SRC:.c=.d))
DEPDIR			:=	dep/
DEPFLAG			=	-MM -MF $@ -MT $@ -MT $(BINDIR)$(addsuffix .o,$(notdir $(basename $<)))
INC				:=	-Ilib/libft/include -Iinc -Ilib/mlx42/include/MLX42
VPATH			=	$(SRCDIR)
CFLAGS			:=	-Wall -Wextra -Werror -ffast-math -O3 -fhonor-infinities -fhonor-nans -fsanitize=address
CPPFLAGS		=	$(INC) -g3
LDFLAGS			:=	-lm lib/libft/libft.a lib/mlx42/build/libmlx42.a -ldl -lglfw -pthread
CC				:=	cc
RM				:=	rm -fr
NAME			:=	minirt_parser

MAKEFLAGS		+=	-r --no-print-directory -j
.EXTRA_PREREQS	=	$(firstword $(MAKEFILE_LIST))
.DEFAULT_GOAL	:=	all
.PRECIOUS		:	$(BINDIR) $(DEPDIR)
.PHONY			:	debug clean fclean re all clangd line unline bypass

-include	$(DEP)

all				:	$(NAME)

$(NAME)			:	$(BIN)
	@echo "\033[G\033[JLinking executable\t[$@]"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(DEPDIR)%.d	:	%.c | $(DEPDIR) line
	@echo "\033[F\033[JGenerating dependencies\t[$(notdir $@)]"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAG) $<
$(BINDIR)%.o	:	%.c	| $(BINDIR) line
	@echo "\033[F\033[JCompiling binary\t[$(notdir $@)]"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

test_%			:	%.o
	$(CC) $(CPPFLAGS) $(TESTFLAGS) -o $@ $< $(TESTDIR)$(basename $<).c $(LDFLAGS)
	./$@

%/				:
	@mkdir -p $@

clean			:
	$(RM) $(BINDIR)

fclean			: | unline
	$(RM) $(BINDIR) 
	$(RM) $(NAME) $(DEPDIR)

re				: | unline
	+$(MAKE) fclean
	+$(MAKE) all

line			:
	@echo ""
unline			:
	@echo -n "\033[F"

bypass			: $(SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(NAME) $^ $(LDFLAGS)

clangd			: | unline
	+@$(MAKE) fclean
	@intercept-build-14 $(MAKE)
