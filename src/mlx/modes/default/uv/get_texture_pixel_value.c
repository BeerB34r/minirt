/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_texture_pixel_value.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 11:26:30 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 16:36:17 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_mlx.h>
#include <math.h>

int	uv_to_xy(double v, int h)
{
	int	w;

	w = floor(v * ((double)h));
	return (w);
}

t_vec4	get_texture_pixel_col(mlx_texture_t *texture, t_tuple coords)
{
	t_vec4		colour;
	uint32_t	c;

	c = (coords.y * texture->width + coords.x) * 4;
	if (c > texture->width * texture->height * 4)
		return ((t_vec4){0, 0, 0, 1});
	colour.x = texture->pixels[c] / 255.0f;
	colour.y = texture->pixels[c + 1] / 255.0f;
	colour.z = texture->pixels[c + 2] / 255.0f;
	colour.w = texture->pixels[c + 3] / 255.0f;
	return (colour);
}

t_vec4	get_texture_pixel_value(mlx_texture_t *texture, t_hit *hit)
{
	t_tuple		coords;
	t_vec4		colour;

	coords.x = uv_to_xy(hit->uv.u, texture->width);
	coords.y = uv_to_xy(hit->uv.v, texture->height);
	colour = get_texture_pixel_col(texture, coords);
	return (colour);
}
