/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 14:25:35 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/12 16:27:17 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <math.h>
#include <stdio.h>

static void	shade_light(t_hit *hit, t_shade_input in, t_vec4 *colour)
{
	t_vec4	light_col;

	in.n = vec3_normalise(hit->shading_normal);
	in.l = vec3_normalise(vec3_sub(in.light.pos, hit->point));
	light_col = get_light_col(in.light);
	in.dot_ln = fmaxf(vec3_dot_product(in.l, in.n), 0.0f);
	vec3_add_inplace(colour, compute_diffuse(
			light_col, in));
	vec3_add_inplace(colour, compute_specular(
			light_col, in));
}

static t_shade_input	make_shade_input(t_rt_element_light light,
										t_material material,
										t_vec3 view_dir)
{
	t_shade_input	in;

	in.light = light;
	in.mat = material;
	in.view_dir = vec3_normalise(view_dir);
	return (in);
}

t_vec4	shade(struct s_rt_scene *scene, t_hit *hit)
{
	t_vec4			light;
	t_material		material;
	t_vec4			colour;
	t_vec3			view_dir;
	unsigned int	i;

	light = (t_vec4){0.0f, 0.0f, 0.0f, 1.0f};
	material = hit->obj->material;
	if (material.texture)
		colour = get_texture_pixel_value(material.texture, hit);
	else
		colour = hex_to_vec4(material.colour.hex);
	if (material.bump_map)
		hit->shading_normal = apply_bump_map(material.bump_map, hit);
	else
		hit->shading_normal = hit->normal;
	view_dir = vec3_normalise(vec3_flip(hit->ray.dir));
	vec3_add_inplace(&light, compute_ambient(
			scene->ambient_light, material.ambi_reflectivity));
	i = -1;
	while (++i < scene->light_count)
		shade_light(hit, make_shade_input(scene->lights[i],
				material, view_dir), &light);
	return (mul_colour(colour, light));
}
