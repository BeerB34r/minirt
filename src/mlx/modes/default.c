/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 16:19:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/01 17:03:56 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>



void	default_color(struct s_mode_func_params p,
							t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
							struct s_rgba *color) {
	 if (!(p.t == p.t)) {
	 	color->hex = PIXEL_TRANSPARENT;
	 	return ;
	}
    // struct s_rt_element *obj = &p.scene->elements[p.obj];
    (void)angles;
    color->r = (char)255;
    color->g = (char)0;
    color->b = (char)0;
    color->a = (char)255; // add lighting
}