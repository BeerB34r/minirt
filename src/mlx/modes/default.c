/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 16:19:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/01 17:32:53 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

#define ITERATIONS 10

void	default_color(struct s_mode_func_params p,
							t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
							struct s_rgba *color) {
	 if (!(p.t == p.t)) {
	 	color->hex = PIXEL_TRANSPARENT;
	 	return ;
	}
    struct s_rt_element *obj = &p.scene->elements[p.obj];

    (void)angles;
	color->hex = (obj->colour.r << 16) | (obj->colour.g << 8) | obj->colour.b; 
    // color->r = obj->colour.r;
    // color->g = obj->colour.g;
    // color->b = obj->colour.b;
}