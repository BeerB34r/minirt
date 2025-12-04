/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/04 16:24:26 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/04 16:48:48 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

t_vec4 hex_to_vec4(uint32_t hex)
{
    t_vec4 colour;

    colour.x = ((hex >> 24) & 0xFF) / 255.0f;
    colour.y = ((hex >> 16) & 0xFF) / 255.0f;
    colour.z = ((hex >> 8)  & 0xFF) / 255.0f;
    colour.w = (hex & 0xFF) / 255.0f;

    return colour;
}

uint32_t vec4_to_hex(t_vec4 c)
{
    return (((uint8_t)(fminf(fmaxf(c.x, 0.0f), 1.0f) * 255.0f) << 24) \
		  | ((uint8_t)(fminf(fmaxf(c.y, 0.0f), 1.0f) * 255.0f) << 16) \
		  | ((uint8_t)(fminf(fmaxf(c.z, 0.0f), 1.0f) * 255.0f) << 8) \
		  | ((uint8_t)(fminf(fmaxf(c.w, 0.0f), 1.0f) * 255.0f)));
}
