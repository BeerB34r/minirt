/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_s.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 17:41:40 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_s.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>

t_uchar	*get_s(t_printf_arg *argument, char *value)
{
	t_uchar	*out;
	size_t	len;

	if (!value)
	{
		if (argument->parameter_precision != maybe && argument->precision < 6)
			out = (t_uchar *)ft_strdup("");
		else
			out = (t_uchar *)ft_strdup("(null)");
	}
	else
	{
		len = ft_strlen(value);
		if (argument->parameter_precision != maybe)
			len = argument->precision;
		out = (t_uchar *)ft_substr(value, 0, len);
	}
	if (!out)
		return (NULL);
	if (argument->width > ft_strlen((char *)out))
		if (pad_s(&out, argument))
			return (free(out), NULL);
	return (out);
}
