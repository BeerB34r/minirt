/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   printf_f.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/09/20 17:27:52 by mde-beer            #+#    #+#           */
/*   Updated: 2025/09/20 19:02:22 by mde-beer            ########   odam.nl   */
/*                                                                            */
/*   —————No norm compliance?——————                                           */
/*   ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                                           */
/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                                           */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                                           */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀                                           */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ——————————————————————————————                                           */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "printf_f.h"
#include <math.h>

static size_t	float_width(double f)
{
	size_t	most_significant_digit;

	modf(f, &f);
	most_significant_digit = 1;
	while (fabs(f) >= 10.0)
	{
		most_significant_digit++;
		f = trunc(f / 10);
	}
	return (most_significant_digit + 6 + 1);
}

static void	populate_float_array(t_uchar *a, double f)
{
	const int	len = float_width(f);
	double		fractional;
	int			i;

	modf(nearbyint(modf(f, &f) * pow(10, 6)), &fractional);
	i = 1;
	while (i < 7)
	{
		a[len - i++] = fmod(fractional, 10) + '0';
		fractional = trunc(fractional / 10);
	}
	a[len - i++] = '.';
	while (len - i >= 0)
	{
		a[len - i++] = fmod(f, 10) + '0';
		f = trunc(f / 10);
	}
}

static t_uchar	*pf_ftoa(double f)
{
	t_uchar	*a;
	size_t	len;

	len = 0;
	if (signbit(f))
		len = 1;
	len += float_width(f);
	a = ft_calloc(len + 1, sizeof(t_uchar));
	if (!a)
		return (NULL);
	if (signbit(f))
		a[0] = '-';
	populate_float_array(&a[!!signbit(f)], fabs(f));
	return (a);
}

t_uchar	*get_float_dec_lo(t_printf_arg *argument, va_list *args)
{
	const double	arg = va_arg(*args, double);

	(void)argument;
	if (arg != arg && signbit(arg))
		return ((t_uchar *)ft_strdup("-nan"));
	if (arg != arg)
		return ((t_uchar *)ft_strdup("nan"));
	if (isinf(arg) && signbit(arg))
		return ((t_uchar *)ft_strdup("-inf"));
	if (isinf(arg))
		return ((t_uchar *)ft_strdup("inf"));
	return (pf_ftoa(arg));
}
