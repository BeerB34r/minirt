/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   apply_bump_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 16:04:16 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 16:44:02 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <minirt_declarations.h>
#include <minirt_mlx.h>

double	coords_to_greyscale(mlx_texture_t *bump_map, t_tuple coords)
{
	t_vec4	col;
	double	luminance;

	col = get_texture_pixel_col(bump_map, coords);
	luminance = ((col.x + col.y + col.z) / 3) * col.w;
	return (luminance);
}

void	get_h(mlx_texture_t *bump_map, t_tuple coords, t_vec3	*h)
{
	uint32_t	original_x;

	original_x = coords.x;
	h->x = coords_to_greyscale(bump_map, coords);
	coords.x = (coords.x + 1) % bump_map->width;
	h->y = coords_to_greyscale(bump_map, coords);
	coords.x = original_x;
	coords.y = (coords.y + 1) % bump_map->height;
	h->z = coords_to_greyscale(bump_map, coords);
}

 // only thing that still needs to be done is to fetch the tangent and bitangent
 // then: normalise(normal + bump_strength * (-u_slope * tangent - v_slope * bitangent))

// t_vec3	apply_bump_map(mlx_texture_t *bump_map, t_hit *hit)
// {
// 	t_tuple		coords;
// 	double		luminance;
// 	t_vec3		h;
// 	double		u_slope;
// 	double		v_slope;

// 	coords.x = uv_to_xy(hit->uv.u, bump_map->width);
// 	coords.y = uv_to_xy(hit->uv.v, bump_map->height);
// 	get_h(bump_map, coords, &h);
// 	u_slope = h.y - h.x;
// 	v_slope = h.z - h.x;
// 	return ();
// }