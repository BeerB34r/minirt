/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 16:19:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/03 16:54:08 by alkuijte      ########   odam.nl         */
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

uint32_t	blend_colour(uint32_t col_a, uint32_t col_b, float weight)
{
	return (((unsigned int)(((col_a >> 24) & 0xFF) * (1.0f - weight)
			+ ((col_b >> 24) & 0xFF) * weight) << 24)
		| ((unsigned int)(((col_a >> 16) & 0xFF) * (1.0f - weight)
			+ ((col_b >> 16) & 0xFF) * weight) << 16)
		| ((unsigned int)(((col_a >> 8) & 0xFF) * (1.0f - weight)
			+ ((col_b >> 8) & 0xFF) * weight) << 8)
		| 0xFF);
}

uint32_t	recursive_default_colour(struct	s_rt_scene *scene, \
									t_line ray, int depth)
{
	unsigned int	obj_i;
	double			t;

	if (depth >= MAX_DEPTH)
		return (PIXEL_BG);
	if (!find_closest_intersection(scene, ray, &obj_i, &t))
		return (PIXEL_BG);	
	// 1. compute hit point + normal
	t_vec3 hit_point = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, t));
    t_vec3 normal = get_normal(scene->elements[obj_i], hit_point);

    // 2. compute diffuse
    // 3. compute shadows
    // 4. compute specular
    // 5. compute object shading color
    // 6. compute reflection_ray
    // 7. recursively compute reflection
    // 8. fresnel blend reflection into shading color

	struct s_rt_element *obj = &scene->elements[obj_i];
    float reflect_weight = 0.5;
    t_line reflected_ray;
    reflected_ray.origin = hit_point;
    reflected_ray.dir = vec3_sub(ray.dir,
                                         vec3_scalar_mul(normal, 2.0 * vec3_dot_product(ray.dir, normal)));
    reflected_ray.dir = vec3_normalise(reflected_ray.dir);
    return blend_colour(obj->colour.hex, recursive_default_colour(scene, reflected_ray, depth + 1), reflect_weight);
}

void	default_color(struct s_mode_func_params p,
                   t_line	angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
                   struct	s_rgba *color)
{
	color->hex = recursive_default_colour(p.scene, angles[p.x][p.y], 0);
}

// TODO add refraction, ambient occlusion, soft shadows, sky gradient BG