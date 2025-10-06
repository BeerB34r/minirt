/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   intersect.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/10/06 10:53:07 by mde-beer            #+#    #+#           */
/*   Updated: 2025/10/06 11:44:49 by mde-beer            ########   odam.nl   */
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

#define MAX_ITER 20
#define INITIAL_GUESS 0.0

static double
	d_superquadric_general_form(
t_sq_gf_arg sq
)
{
	return (
		(sq.r * sq.x * pow(fabs(sq.x / sq.a), -2 + sq.r)) / (sq.a * sq.a)
		+ (sq.s * sq.y * pow(fabs(sq.y / sq.b), -2 + sq.s)) / (sq.b * sq.b)
		+ (sq.t * sq.z * pow(fabs(sq.z / sq.c), -2 + sq.t)) / (sq.c * sq.c)
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

	*t = *t + (superquadric_general_form(sq) / d_superquadric_general_form(sq));
}

static struct s_vec3
	line(
struct s_vec3 origin,
struct s_vec3 normal,
double t
)
{
	return (vec3_add(vec3_scalar_mul(normal, t), origin));
}

static double
	get_sign(
t_sq_gf_arg sq,
struct s_vec3 line_origin,
struct s_vec3 line_vector,
double t
)
{
	const struct s_vec3	internal = line(line_origin, line_vector, t);

	return (superquadric_general_form((t_sq_gf_arg){
			.x = internal.x, .y = internal.y, .z = internal.z,
			.a = sq.a, .b = sq.b, .c = sq.c,
			.r = sq.r, .s = sq.s, .t = sq.t
		}));
}

int
	sq_point_of_intersection(
t_sq_gf_arg sq,
struct s_vec3 line_origin,
struct s_vec3 line_vector,
struct s_vec3 *intersection
)
{
	unsigned int	i;
	double			t;
	double			sign;

	t = INITIAL_GUESS;
	sign = get_sign(sq, line_origin, line_vector, t);
	i = -1;
	while (++i < MAX_ITER && sign != 0)
	{
		newton_iteration(&t, line(line_origin, line_vector, t), sq);
		sign = get_sign(sq, line_origin, line_vector, t);
	}
	if (sign != 0)
		return (1);
	if (intersection)
		*intersection = line(line_origin, line_vector, t);
	return (0);
}
