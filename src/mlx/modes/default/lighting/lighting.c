/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   lighting.c										 :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/04 13:31:52 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/08 18:31:32 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <MLX42.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <math.h>
#include <stdio.h>

// N = surface normal
// V = direction to camera
// L = direction to light
t_vec4	shade(struct s_rt_scene *scene, t_hit *hit, t_line ray)
{
	unsigned int				i;
	struct s_rt_element_light	light;
	t_vec4						light_col;
	t_vec3						n;
	t_vec3						v;
	t_vec3						l;
	t_material					material;
	t_vec4						colour;
	t_vec4						base_colour;
	double						dot_product_ln;

	n = vec3_normalise(hit->normal);
	v = vec3_normalise(vec3_flip(ray.dir));
	material = hit->obj->material;
	colour = (t_vec4){0.0f, 0.0f, 0.0f, 1.0f};
	base_colour = hex_to_vec4(material.colour.hex);
	vec3_add_inplace(&colour, compute_ambient(scene->ambient_light, material));
	i = -1;
	while (++i < scene->light_count)
	{
		light = scene->lights[i];
		light_col = get_light_col(light);
		l = vec3_normalise(vec3_sub(light.pos, hit->point));
		dot_product_ln = fmaxf(vec3_dot_product(l, n), 0.0f);
		vec3_add_inplace(&colour, compute_diffuse(light_col, base_colour, material.diff_reflectivity, dot_product_ln));
		vec3_add_inplace(&colour, compute_specular(light_col, &material, n, v, l, dot_product_ln));
	}
	clamp_colour(&colour);
	return (colour);
}
