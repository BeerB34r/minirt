/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_signed_decimal.c                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 13:48:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/28 17:32:19 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_di.h"
#include <stdarg.h>

t_uchar	*get_signed_decimal(t_printf_arg *argument, va_list *args)
{
	if (argument->length == none)
		return (get_int_i(argument, va_arg(*args, t_sint)));
	if (argument->length == hh)
		return (get_hh_i(argument, (t_schar)va_arg(*args, t_sint)));
	if (argument->length == h)
		return (get_h_i(argument, (t_s_sint)va_arg(*args, t_sint)));
	if (argument->length == l)
		return (get_l_i(argument, va_arg(*args, t_l_sint)));
	if (argument->length == ll)
		return (get_ll_i(argument, va_arg(*args, t_ll_sint)));
	if (argument->length == j)
		return (get_j_i(argument, va_arg(*args, intmax_t)));
	if (argument->length == z)
		return (get_z_i(argument, va_arg(*args, size_t)));
	if (argument->length == t)
		return (get_t_i(argument, va_arg(*args, ptrdiff_t)));
	return (NULL);
}
