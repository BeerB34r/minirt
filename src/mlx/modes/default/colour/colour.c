/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   colour.c										   :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/04 16:03:04 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/08 16:20:44 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

void	clamp_colour_help(double *n)
{
	if (*n < 0.0f)
		*n = 0.0f;
	if (*n > 1.0f)
		*n = 1.0f;
}

void	clamp_colour(t_vec4 *colour)
{
	clamp_colour_help(&colour->x);
	clamp_colour_help(&colour->y);
	clamp_colour_help(&colour->z);
	clamp_colour_help(&colour->w);
}

t_vec4	get_light_col(struct s_rt_element_light light)
{
	t_vec4	base_colour;
	t_vec4	final_colour;

	base_colour = hex_to_vec4(light.colour.hex);
	final_colour = vec3_scalar_mul(base_colour, light.brightness);
	return (final_colour);
}

t_vec4	mul_colour(t_vec4 a, t_vec4 b)
{
	t_vec4	c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return (c);
}

t_vec4	blend_colour(t_vec4 a, t_vec4 b, double r)
{
	t_vec4	left;
	t_vec4	right;

	clamp_colour_help(&r);
	left = vec3_scalar_mul(a, 1.0 - r);
	right = vec3_scalar_mul(b, r);
	return (vec3_add(left, right));
}
