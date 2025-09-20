/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_unsigned_lo_hex.c                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 13:48:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 11:04:53 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_x.h"
#include <stdarg.h>

t_uchar	*get_unsigned_lo_hex(t_printf_arg *argument, va_list *args)
{
	if (argument->length == none)
		return (get_int_x(argument, va_arg(*args, t_uint)));
	if (argument->length == hh)
		return (get_hh_x(argument, (t_schar)va_arg(*args, t_uint)));
	if (argument->length == h)
		return (get_h_x(argument, (t_s_sint)va_arg(*args, t_uint)));
	if (argument->length == l)
		return (get_l_x(argument, va_arg(*args, t_l_uint)));
	if (argument->length == ll)
		return (get_ll_x(argument, va_arg(*args, t_ll_uint)));
	if (argument->length == j)
		return (get_j_x(argument, va_arg(*args, uintmax_t)));
	if (argument->length == z)
		return (get_z_x(argument, va_arg(*args, size_t)));
	if (argument->length == t)
		return (get_t_x(argument, va_arg(*args, ptrdiff_t)));
	return (NULL);
}
