/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   set_pixel_value.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/05 19:11:13 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/05 19:14:35 by mde-beer            ########   odam.nl   */
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
#include <minirt_mlx.h>
#include <stdio.h>

static int	check_intersection(struct s_rt_element object, t_line line, double *t)
{
	double	result;

	result = NAN;

	if (object.type == SUPERQUADRIC) {
		result = sq_int(line, object.superquadric);
	} else if (object.type == SPHERE) {
		result = sphere_int(line, object.sphere);
	} else if (object.type == PLANE) {
		result = plane_int(line, object.plane);
	} else if (object.type == TRIANGLE) {
		result = triangle_int(line, object.triangle);
	} else if (object.type == CYLINDER) {
		result = cylinder_int(line, object.cylinder);
	}
	if (result == result) {
		*t = result;
		return (1);
	}
	return (0);
}

static const struct s_camera_mode	g_modes[] = {
	{HIT_OR_MISS,		hit_or_miss_color},
	{SURFACE_NORMAL,	surface_normal_color}
};

void	get_pixel_value(struct s_get_pixel_params p, t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT], struct s_rgba *out) {
	const unsigned int	x = p.x;
	const unsigned int	y = p.y;
	unsigned int		obj;
	double				t;

	obj = -1;
	t = NAN;
	while (++obj < p.scene->element_count) {
		if (check_intersection(p.scene->elements[obj], angles[x][y], &t)) {
			break;
		}
	}
	g_modes[p.mode].func((struct s_mode_func_params) {
			.scene = p.scene,
			.obj = obj,
			.x = x,
			.y = y,
			.t = t
		},
		angles,
		out
	);
}



// void	get_pixel_value(struct s_get_pixel_params p, t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT], struct s_rgba *out) {
// 	const unsigned int	x = p.x;
// 	const unsigned int	y = p.y;
// 	unsigned int		obj;
// 	unsigned int		closest_obj;
// 	double				t;
// 	double				t_min = INFINITY;

// 	obj = -1;
// 	closest_obj = -1;
// 	while (++obj < p.scene->element_count) {
// 		t = NAN;
// 		if (check_intersection(p.scene->elements[obj], angles[x][y], &t)) {
// 			if (t >= 0 && t < t_min) {
// 				t_min = t;
// 				closest_obj = obj;
// 			}
// 		}
// 	}
// 	g_modes[p.mode].func((struct s_mode_func_params) {
// 			.scene = p.scene,
// 			.obj = closest_obj,
// 			.x = x,
// 			.y = y,
// 			.t = t_min
// 		},
// 		angles,
// 		out
// 	);
// }
