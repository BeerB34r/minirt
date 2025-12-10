/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_texture_pixel_value.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 11:26:30 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 13:26:14 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_mlx.h>
#include <math.h>
#include <stdio.h>

static int	uv_to_xy(double v, int h)
{
	int	w;

	w = (round(v * ((double)h))) * 4;
	return (w);
}

t_vec4	get_texture_pixel_col(mlx_texture_t *texture, int x, int y)
{
	t_vec4	colour;

	colour.x = texture->pixels[y * texture->width + x] / 255.0f;
	colour.y = texture->pixels[(y * texture->width + x) + 1] / 255.0f;
	colour.z = texture->pixels[(y * texture->width + x) + 2] / 255.0f;
	colour.w = texture->pixels[(y * texture->width + x) + 3] / 255.0f;
	return (colour);
}

t_vec4	get_texture_pixel_value(mlx_texture_t *texture, t_hit *hit)
{
	t_tuple		coords;
	t_vec4		colour;

	coords.x = uv_to_xy(hit->uv.u, texture->width);
	coords.y = uv_to_xy(hit->uv.v, texture->height);
	colour = get_texture_pixel_col(texture, coords.x, coords.y);
	return (colour);
}
