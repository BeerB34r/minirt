/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   intersect.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/10/06 10:53:07 by mde-beer            #+#    #+#           */
/*   Updated: 2025/10/06 14:37:57 by mde-beer            ########   odam.nl   */
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

#include <float.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_utils.h>
#include <minirt_math_superquadrics.h>
#include <math.h>
#include <libft.h>
#include <stdio.h>

#define MAX_ITER 200
#define INITIAL_GUESS 0.0

static double
	d_superquadric_general_form(
t_sq_gf_arg sq
)
{
	return (
		(sq.r * sq.x * pow(fabs(sq.x / sq.a), sq.r - 2)) / (sq.a * sq.a)
		+ (sq.s * sq.y * pow(fabs(sq.y / sq.b), sq.s - 2)) / (sq.b * sq.b)
		+ (sq.t * sq.z * pow(fabs(sq.z / sq.c), sq.t - 2)) / (sq.c * sq.c)
		- 1
	);
}

static void
	newton_iteration(
double *t,
struct s_vec3 l_of_t,
t_sq_gf_arg sq_params
)
{
	const t_sq_gf_arg	sq = {
		.x = l_of_t.x, .y = l_of_t.y, .z = l_of_t.z,
		.a = sq_params.a, .b = sq_params.b, .c = sq_params.c,
		.r = sq_params.r, .s = sq_params.s, .t = sq_params.t
	};

	*t = *t - (superquadric_general_form(sq) / d_superquadric_general_form(sq));
}

static double
	get_sign(
t_sq_gf_arg sq,
struct s_vec3 line_origin,
struct s_vec3 line_vector,
double t
)
{
	const struct s_vec3	internal
		= vec3_add(vec3_scalar_mul(line_vector, t), line_origin);

	return (superquadric_general_form((t_sq_gf_arg){
			.x = internal.x, .y = internal.y, .z = internal.z,
			.a = sq.a, .b = sq.b, .c = sq.c,
			.r = sq.r, .s = sq.s, .t = sq.t
		}));
}

static int
	discard_obvious_misses(
t_sq_gf_arg sq,
struct s_vec3 line_origin,
struct s_vec3 line_vector
)
{
	const double	r = (sqrt(3) / 2) * fmax(sq.a, fmax(sq.b, sq.c));
	const double	nabla = pow(vec3_dot_product(line_vector, line_origin), 2)
		- (vec3_dot_product(line_origin, line_origin) - r * r);

	return (nabla < 0);
}

int
	sq_point_of_intersection(
t_sq_gf_arg sq,
struct s_vec3 line_origin,
struct s_vec3 line_vector,
double *intersection
)
{
	unsigned int	i;
	double			t;
	double			sign;

	if (sq.r >= 0 && sq.s >= 0 && sq.t >= 0
		&& discard_obvious_misses(sq, line_origin, line_vector))
		return (1);
	t = INITIAL_GUESS;
	if (intersection)
		t = *intersection;
	sign = get_sign(sq, line_origin, line_vector, t);
	i = -1;
	while (++i < MAX_ITER && sign != 0)
	{
		newton_iteration(&t,
			vec3_add(vec3_scalar_mul(line_vector, t), line_origin), sq);
		sign = get_sign(sq, line_origin, line_vector, t);
	}
	if (trunc(sign * pow(10, 6)) != 0)
		return (1);
	if (intersection)
		*intersection = t;
	return (0);
}
