/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_ambient.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 13:19:36 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 16:43:42 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_mlx.h>

t_vec4	compute_ambient(struct s_rt_element_ambient_light ambient, t_material material)
{
   	float scale = material.ambi_reflectivity;
	t_vec4 material_colour;
	t_vec4 ambient_colour;

	material_colour = hex_to_vec4(material.colour.hex);
	ambient_colour = hex_to_vec4(ambient.colour.hex);
    t_vec4 result;
	result.x = (material_colour.x * scale + ambient_colour.x * (1.0f - scale)) * ambient.ratio;
	result.y = (material_colour.y * scale + ambient_colour.y * (1.0f - scale)) * ambient.ratio;
	result.z = (material_colour.z * scale + ambient_colour.z * (1.0f - scale)) * ambient.ratio;
    result.w = 1.0f;

    return result;
}