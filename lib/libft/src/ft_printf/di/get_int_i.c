/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_int_i.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 13:02:12 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_di.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>

static t_sint	pf_abs(t_sint value)
{
	return (value * (value >= 0) + -value * (value < 0));
}

static void	put_array(t_uchar *out, t_uint index, t_sint value, char *radix)
{
	const t_sint	base = ft_strlen(radix);
	t_sint			div;
	t_sint			mod;

	div = pf_abs(value / base);
	mod = pf_abs(value % base);
	if (index > 0)
		put_array(out, index - 1, div, radix);
	out[index] = radix[mod];
}

static t_uchar	*pf_itoa(t_sint value, t_printf_arg *argument, t_uint numwidth)
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
	{
		outlen = argument->width;
		if (argument->flags & (spaceprefix | signprefix)
			|| value < 0)
			outlen--;
	}
	out = (t_uchar *)ft_calloc(outlen + 1, sizeof(t_uchar));
	if (!out)
		return (NULL);
	put_array(out, outlen - 1, value, "0123456789");
	return (out);
}

static t_uint	get_len(t_sint value)
{
	t_uint	width;

	width = 1;
	while (value / 10)
	{
		width++;
		value /= 10;
	}
	return (width);
}

t_uchar	*get_int_i(t_printf_arg *argument, t_sint value)
{
	const t_uint	numwidth = get_len(value);
	t_uchar			*out;

	if (argument->precision == 0 && value == 0)
		out = (t_uchar *)ft_strdup("");
	else
		out = pf_itoa(value, argument, numwidth);
	if (!out)
		return (NULL);
	if (value < 0 || argument->flags & (spaceprefix | signprefix))
		if (add_sign_i(&out, argument, (value < 0)))
			return (free(out), NULL);
	if (argument->width > ft_strlen((char *)out))
		if (pad_i(&out, argument))
			return (free(out), NULL);
	return (out);
}
