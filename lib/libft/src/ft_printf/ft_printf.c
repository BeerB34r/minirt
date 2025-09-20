/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/19 16:27:29 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/31 15:41:53 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "./libft/libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

static int	combine_parts(t_pf_ret *out, t_uchar *append,\
							t_printf_arg *argument)
{
	t_uchar	*new;
	size_t	len;

	len = ft_strlen((char *)append);
	if (argument->specifier == character)
	{
		len = 1;
		if (argument->width > len)
			len = argument->width;
	}
	new = (t_uchar *)ft_calloc(out->len + len + 1, sizeof(t_uchar));
	if (!new)
	{
		free(append);
		free(out->out);
		return (1);
	}
	ft_memcpy(new, out->out, out->len);
	ft_memcpy(&new[out->len], append, len);
	free(out->out);
	free(append);
	out->out = new;
	out->len += len;
	return (!(out->out));
}

t_pf_ret	ft_printf_chassis(t_uchar *format, va_list *args)
{
	t_printf_arg	argument;
	t_pf_ret		out;
	t_uchar			*backup;
	t_uchar			*temp;

	out = (t_pf_ret){.out = (t_uchar *)ft_strdup(""), .len = 0};
	if (!out.out)
		return ((t_pf_ret){0});
	while (*format)
	{
		backup = format;
		if (*format != '%')
			temp = get_until_arg(&format, &argument);
		else
			temp = get_arg(&argument, &format, args);
		if (temp == backup && !*format)
			break ;
		if (temp == backup)
			temp = (t_uchar *)ft_substr((char *)backup, 0, format - backup);
		if (!temp)
			return (free(out.out), (t_pf_ret){0});
		if (combine_parts(&out, temp, &argument))
			return ((t_pf_ret){0});
	}
	return (out);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list		args;
	t_pf_ret	out;
	int			count;

	va_start(args, format);
	out = ft_printf_chassis((t_uchar *)format, &args);
	if (!out.out)
		return (-1);
	count = write(fd, out.out, out.len);
	return (free(out.out), count);
}

int	ft_sprintf(char *buffer, const char *format, ...)
{
	va_list		args;
	t_pf_ret	out;
	int			count;

	va_start(args, format);
	out = ft_printf_chassis((t_uchar *)format, &args);
	if (!out.out)
		return (-1);
	count = ft_strlcpy(buffer, (char *)out.out, out.len + 1);
	return (free(out.out), count);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_pf_ret	out;
	int			count;

	va_start(args, format);
	out = ft_printf_chassis((t_uchar *)format, &args);
	if (!out.out)
		return (-1);
	count = write(1, out.out, out.len);
	return (free(out.out), count);
}
