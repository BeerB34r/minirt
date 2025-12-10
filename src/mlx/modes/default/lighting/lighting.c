/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 14:25:35 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 12:58:43 by alkuijte      ########   odam.nl         */
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

	in.n = vec3_normalise(hit->normal);
	in.l = vec3_normalise(vec3_sub(in.light.pos, hit->point));
	light_col = get_light_col(in.light);
	in.dot_ln = fmaxf(vec3_dot_product(in.l, in.n), 0.0f);
	vec3_add_inplace(colour, compute_diffuse(
			light_col, in));
	vec3_add_inplace(colour, compute_specular(
			light_col, in));
}

static t_shade_input	make_shade_input(t_rt_element_light light,
										t_vec4 base_colour,
										t_material material,
										t_vec3 view_dir)
{
	t_shade_input	in;

	in.light = light;
	in.base_colour = base_colour;
	in.mat = material;
	in.view_dir = view_dir;
	return (in);
}

t_vec4	shade(struct s_rt_scene *scene, t_hit *hit)
{
	t_vec4			colour;
	t_material		material;
	t_vec4			base_colour;
	t_vec3			view_dir;
	unsigned int	i;

	colour = (t_vec4){0.0f, 0.0f, 0.0f, 1.0f};
	material = hit->obj->material;
	if (material.texture)
		base_colour = get_texture_pixel_value(material.texture, hit);
	else
		base_colour = hex_to_vec4(material.colour.hex);
	view_dir = vec3_normalise(vec3_flip(hit->ray.dir));
	vec3_add_inplace(&colour, compute_ambient(
			scene->ambient_light, material.ambi_reflectivity, base_colour));
	i = -1;
	while (++i < scene->light_count)
		shade_light(hit, make_shade_input(scene->lights[i],
				base_colour, material, view_dir), &colour);
	clamp_colour(&colour);
	return (colour);
}
