CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fPIE -Ofast

PRCN_SRC	=	printf_percent.c
A_LO_SRC	=
A_HI_SRC	=
CHAR_SRC	=	printf_char.c get_c.c
SINT_SRC	=	printf_signed_decimal.c get_signed_decimal_utils.c \
				get_int_i.c get_intmax_i.c get_l_i.c get_ll_i.c \
				get_ptrdiff_i.c get_h_i.c get_hh_i.c get_size_t_i.c
E_LO_SRC	=
E_HI_SRC	=
F_LO_SRC	=	printf_f.c
F_HI_SRC	=
G_LO_SRC	=
G_HI_SRC	=
STOR_SRC	=
OCTA_SRC	=	printf_unsigned_octal.c get_unsigned_octal_utils.c \
				get_int_o.c get_intmax_o.c get_l_o.c get_ll_o.c \
				get_ptrdiff_o.c get_h_o.c get_hh_o.c get_size_t_o.c
PTRH_SRC	=	printf_ptraddr.c get_ptraddr_utils.c get_ptraddr.c
STRN_SRC	=	printf_string.c get_string_utils.c get_s.c
UINT_SRC	=	printf_unsigned_decimal.c get_unsigned_decimal_utils.c \
				get_int_u.c get_intmax_u.c get_l_u.c get_ll_u.c \
				get_ptrdiff_u.c get_h_u.c get_hh_u.c get_size_t_u.c
X_LO_SRC	=	printf_unsigned_lo_hex.c get_unsigned_lo_hex_utils.c \
				get_int_x.c get_intmax_x.c get_l_x.c get_ll_x.c \
				get_ptrdiff_x.c get_h_x.c get_hh_x.c get_size_t_x.c
X_HI_SRC	=	printf_unsigned_hi_hex.c get_unsigned_hi_hex_utils.c \
				get_int_ux.c get_intmax_ux.c get_l_ux.c get_ll_ux.c \
				get_ptrdiff_ux.c get_h_ux.c get_hh_ux.c get_size_t_ux.c
PORC_SRC	=	ft_printf.c printf_parsing.c printf_build_output.c

SRC			=	$(addprefix %/,$(PRCN_SRC)) $(addprefix a/,$(A_LO_SRC)) \
				$(addprefix u_a/,$(A_HI_SRC)) $(addprefix c/,$(CHAR_SRC)) \
				$(addprefix di/,$(SINT_SRC)) $(addprefix e/,$(E_LO_SRC)) \
				$(addprefix u_e/,$(E_HI_SRC)) $(addprefix f/,$(F_LO_SRC)) \
				$(addprefix u_f/,$(F_HI_SRC)) $(addprefix g/,$(G_LO_SRC)) \
				$(addprefix u_g/,$(G_HI_SRC)) $(addprefix n/,$(STOR_SRC)) \
				$(addprefix o/,$(OCTA_SRC)) $(addprefix p/,$(PTRH_SRC)) \
				$(addprefix s/,$(STRN_SRC)) $(addprefix u/,$(UINT_SRC)) \
				$(addprefix x/,$(X_LO_SRC)) $(addprefix u_x/,$(X_HI_SRC)) \
				$(PORC_SRC)

OBJ			=	$(SRC:.c=.o)
NAME		=	$(LIBFPF)

all			:	$(NAME)

$(NAME)		:	$(OBJ)
			ar -rcs $@ $?

%.o			:	%.c
			$(CC) $(CFLAGS) -c -o $@ $^

fclean		:	clean
			rm -f $(NAME)

clean		:
			rm -f $(OBJ)

debug		:	fclean
			$(MAKE) CFLAGS="$(CFLAGS) -g" all

re			:	fclean all

.PHONY		:	fclean clean all re bonus
