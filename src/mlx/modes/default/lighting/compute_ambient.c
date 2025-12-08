/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_ambient.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 13:19:36 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 14:03:58 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_mlx.h>

t_vec4	compute_ambient(struct s_rt_element_ambient_light ambient, t_vec4 colour)
{
	t_vec4 ambient_light = hex_to_vec4(ambient.colour.hex);
	
	return (blend_colour(colour, ambient_light, ambient.ratio));
}