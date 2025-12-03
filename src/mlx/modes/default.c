/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   default.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 16:19:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/03 15:42:05 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

#define MAX_DEPTH 10

uint32_t blend_colour(uint32_t col_A, uint32_t col_B, float reflect_weight)
{
    uint32_t col_C;

    // Extract RGB from hex
    unsigned int rA = (col_A >> 16) & 0xFF;
    unsigned int gA = (col_A >> 8)  & 0xFF;
    unsigned int bA = col_A & 0xFF;

    unsigned int rB = (col_B >> 16) & 0xFF;
    unsigned int gB = (col_B >> 8)  & 0xFF;
    unsigned int bB = col_B & 0xFF;

    // Blend each channel
    unsigned int rC = (unsigned int)(rA * (1.0f - reflect_weight) + rB * reflect_weight);
    unsigned int gC = (unsigned int)(gA * (1.0f - reflect_weight) + gB * reflect_weight);
    unsigned int bC = (unsigned int)(bA * (1.0f - reflect_weight) + bB * reflect_weight);

    // Recombine into hex
    col_C = (rC << 16) | (gC << 8) | bC;

    return col_C;
}

uint32_t recursive_default_colour(struct s_rt_scene *scene, t_line ray, int depth)
{
	uint32_t colour;
	uint32_t reflected_colour;
    unsigned int obj_i;
    double t;

    if (depth >= MAX_DEPTH || !find_closest_intersection(scene, ray, &obj_i, &t))
    {
		return PIXEL_TRANSPARENT;
    }

	struct s_rt_element *obj = &scene->elements[obj_i];
	if (obj->colour.hex != PIXEL_TRANSPARENT && obj->colour.hex != PIXEL_BLACK) { 
		colour = obj->colour.hex;
	} else {
		colour = PIXEL_RED;
	}
	// if (obj_i == 0) {
	// 	colour.hex = PIXEL_RED;
	// } else if (obj_i == 1) {
	// 	colour.hex = PIXEL_GRE;
	// } else if (obj_i == 2) {
	// 	colour.hex = PIXEL_BLU;
	// } else {
	// 	colour.hex = PIXEL_WHITE;
	// }

	t_vec3 hit_point = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, t));
    t_vec3 normal = get_normal(scene->elements[obj_i], hit_point);
  //  float reflect_weight = 0.5;
    t_line reflected_ray;
    reflected_ray.origin = hit_point;
    reflected_ray.dir = vec3_sub(ray.dir,
                                         vec3_scalar_mul(normal, 2.0 * vec3_dot_product(ray.dir, normal)));
    reflected_ray.dir = vec3_normalise(reflected_ray.dir);

	reflected_colour = recursive_default_colour(scene, reflected_ray, depth + 1);

    // colour = blend_colour(colour, reflected_colour, reflect_weight);
	//colour = obj->colour.hex;
	//colour = PIXEL_RED;
    return colour;
}


void default_color(struct s_mode_func_params p,
                   t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
                   struct s_rgba *color)
{
	t_line ray = angles[p.x][p.y];
	color->hex = recursive_default_colour(p.scene, ray, 0);
    // color->hex = blend_colour(color->hex, recursive_default_colour(p.scene, ray, 0), 0.5f);
}