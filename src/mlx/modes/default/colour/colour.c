/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/04 16:03:04 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 14:07:33 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>


t_vec4	fresnel_blend(t_vec4 col_a, t_vec4 col_b, float iot)
{
	t_vec4 col_c = {0, 0, 0};
	(void)col_a;
	(void)col_b;
	(void)iot;
	return (col_c);
}

t_vec4 get_light_col(struct s_rt_element_light light)
{
	t_vec4 base_colour;
	t_vec4	final_colour;

	base_colour = hex_to_vec4(light.colour.hex);
	final_colour = vec3_scalar_mul(base_colour, light.brightness);
	return (final_colour);
}

t_vec4 blend_colour(t_vec4 a, t_vec4 b, double r)
{
    if (r < 0.0) r = 0.0;
    if (r > 1.0) r = 1.0;

    t_vec4 left  = vec3_scalar_mul(a, 1.0 - r);
    t_vec4 right = vec3_scalar_mul(b, r);

    return vec3_add(left, right);
}

