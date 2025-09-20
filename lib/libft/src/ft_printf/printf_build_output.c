/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_build_output.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/25 17:36:11 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 16:26:46 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft/libft.h"

void	parse_arg(t_printf_arg *argument, t_uchar **format)
{
	(*format)++;
	parse_flag(argument, format);
	parse_width(argument, format);
	parse_precision(argument, format);
	parse_length(argument, format);
	parse_specifier(argument, format);
}

void	clear_arg(t_printf_arg *argument)
{
	argument->flags = noflag;
	argument->parameter_width = maybe;
	argument->width = 0;
	argument->parameter_precision = maybe;
	argument->precision = 1;
	argument->length = none;
	argument->specifier = no_specifier;
}

t_uchar	*get_arg(t_printf_arg *argument, t_uchar **format, va_list *args)
{
	const t_uchar	*backup = *format;

	clear_arg(argument);
	parse_arg(argument, format);
	if (argument->specifier == no_specifier)
		return ((t_uchar *)backup);
	if (argument->parameter_width == truey)
		argument->width = va_arg(*args, unsigned int);
	if (argument->parameter_precision == truey)
		argument->precision = va_arg(*args, unsigned int);
	return (g_specifiers[argument->specifier - 1](argument, args));
}

t_uchar	*get_until_arg(t_uchar **format, t_printf_arg *argument)
{
	t_uchar	*out;
	size_t	i;

	clear_arg(argument);
	i = 0;
	while ((*format)[i] && (*format)[i] != '%')
		i++;
	out = (t_uchar *)ft_substr((char *)*format, 0, i);
	*format += i;
	return (out);
}
