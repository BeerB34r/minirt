/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_intmax_i.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:22 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 13:02:23 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "printf_di.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>

static intmax_t	pf_abs(intmax_t value)
{
	return (value * (value >= 0) + -value * (value < 0));
}

static void	put_array(t_uchar *out, t_uint index,
						intmax_t value, char *radix)
{
	const t_sint	base = ft_strlen(radix);
	intmax_t		div;
	intmax_t		mod;

	div = pf_abs(value / base);
	mod = pf_abs(value % base);
	if (index > 0)
		put_array(out, index - 1, div, radix);
	out[index] = radix[mod];
}

static t_uchar	*pf_itoa(intmax_t value, t_printf_arg *argument,
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

static t_uint	get_len(intmax_t value)
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

t_uchar	*get_j_i(t_printf_arg *argument, intmax_t value)
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
