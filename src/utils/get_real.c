/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   get_real.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/09/19 16:48:03 by mde-beer            #+#    #+#           */
/*   Updated: 2025/09/19 20:02:39 by mde-beer            ########   odam.nl   */
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

#include <libft.h>
#include <math.h>
#include <minirt_error.h>

static int
	strcasecmp(
const char *a,
const char *b
)
{
	int	res;

	while (*a && *b)
	{
		res = ft_tolower(*a++) - ft_tolower(*b++);
		if (res)
			return (res);
	}
	return (ft_tolower(*a) - ft_tolower(*b));
}

static double
	atof(
const char *str
)
{
	double	res;
	int		sign;
	int		i;
	int		decimal;

	i = (str[0] == '-');
	sign = -((i * 2) - 1);
	res = 0.0 * sign;
	if (!strcasecmp(&str[i], "inf") || !strcasecmp(&str[i], "infinity"))
		return (INFINITY * sign);
	if (!ft_isdigit(str[i]) && str[i] != '.')
		return (NAN);
	while (str[i] && ft_isdigit(str[i]))
		res = fma(res, 10, (str[i++] - 0x30) * sign);
	if (str[i] && !(str[i] == '.' || ft_tolower(str[i]) == 'f'))
		return (NAN);
	if (!str[i] || str[i] != '.')
		return (res);
	i++;
	decimal = 1;
	while (str[i] && ft_isdigit(str[i]))
		res = fma((str[i++] - 0x30) * sign, pow(0.1, decimal++), res);
	if (str[i] && (str[i + 1] || ft_tolower(str[i]) != 'f'))
		return (NAN);
	return (res);
}

int
	get_real(
const char *str,
double *store
)
{
	const double	result = atof(str);

	if (isnan(result))
	{
		ft_dprintf(2, ERR E_NOTR, str);
		return (1);
	}
	*store = result;
	return (0);
}
