/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_signed_decimal_utils.c                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/25 11:53:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/28 18:03:09 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../printf_datatypes.h"
#include <stdlib.h>

int	add_sign_i(char **out, t_printf_arg *argument, int negative)
{
	char *const	ret = (char *)ft_calloc(ft_strlen(*out) + 2, sizeof(char));
	char		sign;

	if (!ret)
		return (1);
	sign = ' ';
	if (negative)
		sign = '-';
	else if (argument->flags & signprefix)
		sign = '+';
	ret[0] = sign;
	ft_strlcpy(ret + 1, *out, ft_strlen(*out) + 1);
	free(*out);
	*out = ret;
	return (0);
}

int	pad_i(char **out, t_printf_arg *argument)
{
	const unsigned int	padding = argument->width - ft_strlen(*out);
	char *const			padstr = (char *)ft_calloc(padding + 1, sizeof(char));
	char				*ret;
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
		ret = ft_strjoin(*out, padstr);
	else
		ret = ft_strjoin(padstr, *out);
	free(*out);
	free(padstr);
	*out = ret;
	return (!ret);
}
