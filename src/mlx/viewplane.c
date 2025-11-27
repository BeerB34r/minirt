/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   viewplane.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/10/31 19:08:55 by mde-beer            #+#    #+#           */
/*   Updated: 2025/10/31 19:12:05 by mde-beer            ########   odam.nl   */
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
#include <minirt_mlx.h>
#include <minirt_math.h>
#include <stdio.h>

static void view_plane_array(t_line array[VIEWPORT_WIDTH][VIEWPORT_HEIGHT], t_plane_array_opts opt) {
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < opt.w) {
		j = -1;
		while (++j < opt.h) {
			array[i][j] = (t_line){.origin = opt.origin, .normal = vec3_normalise(vec3_add(vec3_add(opt.p_1m, vec3_scalar_mul(opt.q_x, i)), vec3_scalar_mul(opt.q_y, j)))};
		}
	}
}

t_norm
	local_y(
t_norm local_x
)
{
	const t_norm	x = (t_norm){.x = 1, .y = 0, .z = 0};
	const t_norm	y = (t_norm){.x = 0, .y = 1, .z = 0};
	const double	theta = acos(vec3_dot_product(local_x, x));
	t_norm			k;

	k = vec3_normalise(vec3_cross_product(local_x, x));
	if (vec3_magnitude(k) == vec3_magnitude(k))
		;
	else
		k = (t_norm){.x = 1, .y = 0, .z = 0};
	return (vec3_normalise(
			vec3_add(
				vec3_scalar_mul(y, cos(theta)),
				vec3_add(
					vec3_scalar_mul(
						vec3_cross_product(k, y),
						sin(theta)),
					vec3_scalar_mul(
						vec3_scalar_mul(
							k, vec3_dot_product(k, y)),
						1 - cos(theta))))));
}

t_norm	local_z(t_norm local_x) {
	const t_norm	x = (t_norm){.x = 1, .y = 0, .z = 0};
	const t_norm	z = (t_norm){.x = 0, .y = 0, .z = 1};
	const double	theta = acos(vec3_dot_product(local_x, x));
	t_norm			k;

	k = vec3_normalise(vec3_cross_product(local_x, x));
	if (vec3_magnitude(k) == vec3_magnitude(k))
		;
	else
		k = (t_norm){.x = 1, .y = 0, .z = 0};
	return (vec3_normalise(
			vec3_add(
				vec3_scalar_mul(z, cos(theta)),
				vec3_add(
					vec3_scalar_mul(
						vec3_cross_product(k, z),
						sin(theta)),
					vec3_scalar_mul(
						vec3_scalar_mul(
							k, vec3_dot_product(k, z)),
						1 - cos(theta))))));
}

void	populate_plane_array(struct s_rt_element_camera c, unsigned int w, unsigned int h,
								t_line array[VIEWPORT_WIDTH][VIEWPORT_HEIGHT]) {
	const double	theta = c.fov * (M_PI / 180);
	const double	g_y = tan(theta / 2) * ((h - 1.0) / (w - 1.0));
	const t_vec3	q_x = vec3_scalar_mul(local_z(c.orientation),
			(2 * tan(theta / 2)) / (w - 1));
	const t_vec3	q_y = vec3_scalar_mul(local_y(c.orientation),
			(2 * g_y) / (h - 1));
	const t_vec3	p_1m = vec3_sub(vec3_sub(
				c.orientation, vec3_scalar_mul((t_norm){
					.x = c.orientation.z,
					.y = c.orientation.x,
					.z = c.orientation.y
				}, tan(theta / 2))),
			vec3_scalar_mul((t_norm){
				.x = c.orientation.y,
				.y = c.orientation.z,
				.z = c.orientation.x
			}, g_y));

	view_plane_array(array, (t_plane_array_opts){.origin = c.pos,
		.w = w, .h = h,
		.p_1m = p_1m,
		.q_x = q_x,
		.q_y = q_y});
}
