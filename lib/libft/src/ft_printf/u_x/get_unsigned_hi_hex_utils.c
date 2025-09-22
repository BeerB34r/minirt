/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_unsigned_hi_hex_utils.c                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/25 11:53:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 12:22:30 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../printf_datatypes.h"
#include <stdlib.h>

t_uint	add_base_ux(t_uchar **out)
{
	const char		*prefix = "0X";
	t_uchar *const	ret = (t_uchar *)ft_strjoin(prefix, (char *)(*out));

	free(*out);
	*out = ret;
	return (!ret);
}

t_uint	pad_ux(t_uchar **out, t_printf_arg *argument)
{
	const t_uint		padding = argument->width - ft_strlen((char *)(*out));
	char *const			padstr = (char *)ft_calloc(padding + 1, sizeof(char));
	t_uchar				*ret;
	char				padchar;

	if (!padstr)
		return (1);
	padchar = ' ';
	if (argument->parameter_precision == maybe
		&& argument->flags & zeropad
		&& !(argument->flags & leftjustify))
		padchar = '0';
	ft_memset(padstr, padchar, padding);
	if (argument->flags & leftjustify)
		ret = (t_uchar *)ft_strjoin((char *)*out, padstr);
	else
		ret = (t_uchar *)ft_strjoin(padstr, (char *)*out);
	free(*out);
	free(padstr);
	*out = ret;
	return (!ret);
}
