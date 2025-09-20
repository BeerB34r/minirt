/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_parsing.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/25 17:29:31 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 16:27:02 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf_datatypes.h"

void	parse_flag(t_printf_arg *argument, char **format)
{
	while (ft_isinset(**format, FLAGS) != -1)
	{
		if (**format == '-')
			argument->flags |= leftjustify;
		if (**format == '#')
			argument->flags |= baseprefix;
		if (**format == ' ')
			argument->flags |= spaceprefix;
		if (**format == '+')
			argument->flags |= signprefix;
		if (**format == '0')
			argument->flags |= zeropad;
		(*format)++;
	}
}

void	parse_width(t_printf_arg *argument, char **format)
{
	if (**format == '*')
	{
		argument->parameter_width = truey;
		(*format)++;
		return ;
	}
	if (ft_isdigit(**format))
	{
		argument->parameter_width = falsey;
		argument->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
}

void	parse_precision(t_printf_arg *argument, char **format)
{
	if (**format != '.')
		return ;
	(*format)++;
	if (**format == '*')
	{
		argument->parameter_precision = truey;
		(*format)++;
		return ;
	}
	argument->parameter_precision = falsey;
	if (ft_isdigit(**format))
	{
		argument->precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
		return ;
	}
	argument->precision = 0;
}

void	parse_length(t_printf_arg *argument, char **format)
{
	if (ft_isinset(**format, LENGTH) == -1)
		return ;
	if (**format == 'h')
		argument->length = h;
	if (**format == 'l')
		argument->length = l;
	if (**format == 'j')
		argument->length = j;
	if (**format == 'z')
		argument->length = z;
	if (**format == 't')
		argument->length = t;
	if (**format == 'L')
		argument->length = u_l;
	(*format)++;
	if (argument->length == l)
		if (**format == 'l')
			argument->length = ll;
	if (argument->length == h)
		if (**format == 'h')
			argument->length = hh;
	if (argument->length == ll || argument->length == hh)
		(*format)++;
}

void	parse_specifier(t_printf_arg *argument, char **format)
{
	int				ret;

	ret = ft_isinset(**format, SPECIFIER);
	if (ret == 0)
		ret = 1;
	if (ret == -1)
		ret = 0;
	argument->specifier = ret;
	if (ret)
		(*format)++;
}
