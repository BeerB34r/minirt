/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_string_utils.c                                  :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/25 11:53:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/30 18:26:37 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../printf_datatypes.h"
#include <stdlib.h>

t_uint	pad_s(t_uchar **out, t_printf_arg *argument)
{
	const t_uint		padding = argument->width - ft_strlen((char *)(*out));
	char *const			padstr = (char *)ft_calloc(padding + 1, sizeof(char));
	t_uchar				*ret;
	const char			padchar = ' ';

	if (!padstr)
		return (1);
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
