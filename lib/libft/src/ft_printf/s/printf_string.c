/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_string.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 13:48:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 17:42:43 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_s.h"
#include <stdarg.h>

t_uchar	*get_string(t_printf_arg *argument, va_list *args)
{
	return (get_s(argument, va_arg(*args, char *)));
}
