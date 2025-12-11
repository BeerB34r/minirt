/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_uv.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 13:54:05 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 11:32:39 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_math.h>
#include <math.h>
#include <stdio.h>

// Must be called after get_plane_tangents
void	get_plane_uv(t_uv *uv, t_vec3 p)
{
	double	scale;

	scale = 7.0f;
	uv->u = vec3_dot_product(p, uv->t);
	uv->v = vec3_dot_product(p, uv->b);
	uv->u = fmod(uv->u / scale, 1.0);
	if (uv->u < 0.0)
		uv->u += 1.0;
	uv->v = fmod(uv->v / scale, 1.0);
	if (uv->v < 0.0)
		uv->v += 1.0;
}
