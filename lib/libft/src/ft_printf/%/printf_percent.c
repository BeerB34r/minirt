/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_percent.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/21 13:48:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 18:25:52 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_percent.h"
#include "../libft/libft.h"
#include <stdarg.h>

t_uchar	*get_percent(t_printf_arg *argument, va_list *args)
{
	(void)args;
	(void)argument;
	return ((t_uchar *)ft_strdup("%"));
}
