/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/04 16:03:04 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/04 16:46:34 by alkuijte      ########   odam.nl         */
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

t_vec4 blend_colour(t_vec4 col_a, t_vec4 col_b, double ratio)
{
    t_vec4 result;

    result.x = col_a.x * ratio + col_b.x * (1.0f - ratio);
    result.y = col_a.y * ratio + col_b.y * (1.0f - ratio);
    result.z = col_a.z * ratio + col_b.z * (1.0f - ratio);
    result.w = col_a.w * ratio + col_b.w * (1.0f - ratio);

    if (result.x > 1.0f) result.x = 1.0f;
    if (result.y > 1.0f) result.y = 1.0f;
    if (result.z > 1.0f) result.z = 1.0f;
    if (result.w > 1.0f) result.w = 1.0f;

    return result;
}

t_vec4	compute_ambient(struct s_rt_element_ambient_light ambient, t_vec4 colour)
{
	t_vec4 ambient_light = hex_to_vec4(ambient.color.hex);
	
	return (blend_colour(colour, ambient_light, ambient.ratio));
}