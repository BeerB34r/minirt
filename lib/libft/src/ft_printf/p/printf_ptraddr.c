/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_ptraddr.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 13:48:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 14:10:46 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include <stdarg.h>

t_uchar	*get_ptraddr(t_printf_arg *argument, va_list *args)
{
	return (get_p(argument, va_arg(*args, void *)));
}
