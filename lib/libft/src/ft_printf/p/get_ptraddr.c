/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_ptraddr.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 12:53:56 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_p.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>

static void	put_array(t_uchar *out, t_uint index,
						uintptr_t value, char *radix)
{
	const t_uint	base = ft_strlen(radix);
	uintptr_t		div;
	uintptr_t		mod;

	div = value / base;
	mod = value % base;
	if (index > 0)
		put_array(out, index - 1, div, radix);
	out[index] = radix[mod];
}

static t_uchar	*pf_itoa(uintptr_t value, t_printf_arg *argument,
							t_uint numwidth)
{
	t_uchar	*out;
	t_uint	outlen;

	outlen = numwidth;
	if (argument->parameter_precision != maybe
		&& argument->precision > numwidth)
		outlen = argument->precision;
	else if (argument->parameter_precision == maybe
		&& argument->width > numwidth
		&& argument->flags & zeropad
		&& !(argument->flags & leftjustify))
		outlen = argument->width;
	out = (t_uchar *)ft_calloc(outlen + 1, sizeof(t_uchar));
	if (!out)
		return (NULL);
	put_array(out, outlen - 1, value, "0123456789abcdef");
	return (out);
}

static t_uint	get_len(uintptr_t value)
{
	t_uint	width;

	width = 1;
	while (value / 16)
	{
		width++;
		value /= 16;
	}
	return (width);
}

t_uchar	*get_p(t_printf_arg *argument, void *value)
{
	const uintptr_t	val = (uintptr_t)value;
	const t_uint	numwidth = get_len(val);
	t_uchar			*out;

	if (val == 0)
		out = (t_uchar *)ft_strdup("(nil)");
	else
		out = pf_itoa(val, argument, numwidth);
	if (!out)
		return (NULL);
	if (val != 0)
		if (add_base_p(&out))
			return (NULL);
	if (argument->width > ft_strlen((char *)out))
		if (pad_p(&out, argument))
			return (free(out), NULL);
	return (out);
}
