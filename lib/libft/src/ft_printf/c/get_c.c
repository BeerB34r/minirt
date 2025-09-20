/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_c.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 14:39:52 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_c.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>

t_uchar	*get_c(t_printf_arg *argument, int value)
{
	t_uchar			*out;

	if (argument->width <= 0)
		argument->width = 1;
	if (argument->width > 1)
		out = ft_calloc(sizeof(t_uchar), argument->width + 1);
	else
		out = ft_calloc(sizeof(t_uchar), 2);
	if (!out)
		return (NULL);
	if (argument->flags & leftjustify)
	{
		out[0] = (t_uchar)value;
		ft_memset(out + 1, ' ', argument->width - 1);
	}
	else
	{
		ft_memset(out, ' ', argument->width - 1);
		out[argument->width - 1] = (t_uchar)value;
	}
	return (out);
}
