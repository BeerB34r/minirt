/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 16:19:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/04 16:55:34 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

#define MAX_DEPTH 25

// uint32_t	blend_colour(uint32_t col_a, uint32_t col_b, float weight)
// {
// 	return (((unsigned int)(((col_a >> 24) & 0xFF) * (1.0f - weight)
// 			+ ((col_b >> 24) & 0xFF) * weight) << 24)
// 		| ((unsigned int)(((col_a >> 16) & 0xFF) * (1.0f - weight)
// 			+ ((col_b >> 16) & 0xFF) * weight) << 16)
// 		| ((unsigned int)(((col_a >> 8) & 0xFF) * (1.0f - weight)
// 			+ ((col_b >> 8) & 0xFF) * weight) << 8)
// 		| 0xFF);
// }

// t_vec4	reflect(t_vec4 v, t_vec4 n) {
// 	return (vec3_sub(v, vec3_scalar_mul(n, 2.0f * vec3_dot_product(v, n))));
// }

// double fresnel_schlick(double cosx, double ior)
// {
//     double r0 = (1 - ior) / (1 + ior);
//     r0 = r0 * r0;
//     return r0 + (1 - r0) * pow(1 - cosx, 5);
// }

uint32_t trace_ray(struct s_rt_scene *scene,
                                  t_line ray, int depth)
{
	t_hit	hit;
	uint32_t final_colour;

    if (depth >= MAX_DEPTH)
        return PIXEL_BG;

    if (!find_closest_intersection(scene, ray, &hit))
        return PIXEL_BG;

    hit.point = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, hit.t));
    hit.normal = get_normal(*hit.obj, hit.point);
    if (vec3_dot_product(ray.dir, hit.normal) > 0) {
        hit.normal = vec3_scalar_mul(hit.normal, -1);
	}
	final_colour = vec4_to_hex(shade(scene, &hit, ray, depth));
    return (final_colour);
}


void	default_color(struct s_mode_func_params p,
                   t_line	angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
                   struct	s_rgba *color)
{
	color->hex = trace_ray(p.scene, angles[p.x][p.y], 0);
}

// TODO add refraction, ambient occlusion, soft shadows, sky gradient BG