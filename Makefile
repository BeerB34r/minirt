SRC				!=	cat src.list
SRCDIR			=	src/utils/ src/parsing/ src/ 
TESTDIR			=	test/
TESTFLAGS		=	-g3
BIN				=	$(addprefix $(BINDIR),$(SRC:.c=.o))
BINDIR			=	bin/
DEP				=	$(addprefix $(DEPDIR),$(SRC:.c=.d))
DEPDIR			=	dep/
DEPFLAG			=	-MM -MF $@ -MT $@ -MT $(BINDIR)$(addsuffix .o,$(notdir $(basename $<)))
INC				=	-Ilib/libft/include -I inc
VPATH			=	$(SRCDIR)
CFLAGS			:=	-Wall -Wextra -Werror -O3 -ffast-math -fhonor-infinities -fhonor-nans
CPPFLAGS		=	$(INC)
LDFLAGS			=	-lm lib/libft/libft.a
CC				:=	cc
NAME			:=	minirt_parser

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
	mkdir -p $@

clean			:
	$(RM) -r $(BINDIR)

fclean			:
	$(RM) -r $(BINDIR)
	$(RM) -r $(DEPDIR)
	$(RM) $(NAME)

re				:
	$(MAKE) fclean
	+$(MAKE) all
