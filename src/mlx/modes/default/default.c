/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 16:19:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 18:10:14 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

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

t_vec4 trace_ray(struct s_rt_scene *scene,
                                  t_line ray, int depth)
{
	t_hit	hit;
	t_vec4 bg = hex_to_vec4(PIXEL_BG);

    if (depth >= MAX_DEPTH)
        return bg;

    if (!find_closest_intersection(scene, ray, &hit))
        return bg;

    hit.point = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, hit.t));
    hit.normal = get_normal(*hit.obj, hit.point);
    if (vec3_dot_product(ray.dir, hit.normal) > 0) {
        hit.normal = vec3_scalar_mul(hit.normal, -1);
	}
	t_vec4 colour = shade(scene, &hit, ray);
    float refl = hit.obj->material.abso_reflectivity;
    if (refl > 0.0f && depth + 1 < MAX_DEPTH)
    {
        t_vec3 I = vec3_normalise(ray.dir);
        t_vec3 R = reflect(I, hit.normal);

        t_line reflection_ray;
        reflection_ray.origin = vec3_add(hit.point,
                                         vec3_scalar_mul(hit.normal, EPSILON));
        reflection_ray.dir = R;

        t_vec4 reflected = trace_ray(scene, reflection_ray, depth + 1);

        colour = blend_colour(colour, reflected, refl);
    }
	colour = vec3_scalar_mul(colour, EXPOSURE);
    return colour;
}


void	default_colour(struct s_mode_func_params p,
                   t_line	angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
                   struct	s_rgba *colour)
{
    t_vec4 float_colour = trace_ray(p.scene, angles[p.x][p.y], 0);
    colour->hex = vec4_to_hex(float_colour);
}

// TODO add refraction, ambient occlusion, soft shadows, sky gradient BG