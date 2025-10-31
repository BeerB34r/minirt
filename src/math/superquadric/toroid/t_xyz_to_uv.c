/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   xyz_to_uv.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/10/24 08:24:08 by mde-beer            #+#    #+#           */
/*   Updated: 2025/10/24 08:39:11 by mde-beer            ########   odam.nl   */
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

#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>

static t_uv
	guess_1(
t_vec3 p,
struct s_rt_element_superquadric s
)
{
	const double	u = asin(pow(p.z / s.a3, 1 / s.a3));
	double			vx;
	double			vy;

	if (!(cos(u) + s.a4))
		return ((t_uv){.u = u, .v = 0});
	vx = acos(pow(p.x / (s.a1 * (s.a4 + pow(cos(u), s.e1))), 1 / s.e2));
	vx = fmin(vx, 1.0);
	vy = asin(pow(p.y / (s.a2 * (s.a4 + pow(cos(u), s.e1))), 1 / s.e2));
	return ((t_uv){.u = u, .v = copysign(vx, vy)});
}

static t_uv
	guess_2(
t_uv guess_1,
t_vec3 p,
struct s_rt_element_superquadric s
)
{
	const double	u = copysign(fabs(fabs(guess_1.u) - M_PI), p.z);
	double			vx;
	double			vy;

	if (!(cos(u) + s.a4))
		return ((t_uv){.u = u, .v = 0});
	vx = acos(pow(p.x / (s.a1 * (s.a4 + pow(cos(u), s.e1))), 1 / s.e2));
	vx = fmin(vx, 1.0);
	vy = asin(pow(p.y / (s.a2 * (s.a4 + pow(cos(u), s.e1))), 1 / s.e2));
	return ((t_uv){.u = u, .v = copysign(vx, vy)});
}

static t_vec3
	uv_xyz(
t_uv uv,
struct s_rt_element_superquadric s
)
{
	return ((t_vec3){
		.x = s.a1 * (s.a4 + pow(cos(uv.u), s.e1)) * pow(cos(uv.v), s.e2),
		.y = s.a2 * (s.a4 + pow(cos(uv.u), s.e1)) * pow(sin(uv.v), s.e2),
		.z = s.a3 * pow(sin(uv.u), s.e1)
	});
}

t_uv
	sq_t_xyz_uv(
t_vec3 pw,
struct s_rt_element_superquadric s
)
{
	const t_vec3	p = sq_wp_op(pw, s);
	const t_uv		g1 = guess_1(p, s);
	const t_uv		g2 = guess_2(g1, p, s);
	const double	absp1 = vec3_magnitude(vec3_sub(uv_xyz(g1, s), p));
	const double	absp2 = vec3_magnitude(vec3_sub(uv_xyz(g2, s), p));

	if (absp2 == absp2 && absp1 > absp2)
		return (g2);
	return (g1);
}
