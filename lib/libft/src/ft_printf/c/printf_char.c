/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_char.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 13:48:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 16:45:00 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_c.h"
#include <stdarg.h>

t_uchar	*get_char(t_printf_arg *argument, va_list *args)
{
	return (get_c(argument, va_arg(*args, int)));
}
