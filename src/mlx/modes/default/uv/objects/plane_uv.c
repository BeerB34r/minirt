/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_uv.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 13:54:05 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 15:39:53 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_math.h>
#include <math.h>
#include <stdio.h>

void	get_plane_uv(t_uv *uv, t_vec3 p, t_vec3 normal)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	double	scale;

	scale = 7.0f;
	if (fabs(normal.x) > fabs(normal.y))
		tangent = vec3_normalise(vec3_cross_product((t_vec3){0, 1, 0}, normal));
	else
		tangent = vec3_normalise(vec3_cross_product((t_vec3){1, 0, 0}, normal));
	bitangent = vec3_cross_product(normal, tangent);
	uv->u = vec3_dot_product(p, tangent);
	uv->v = vec3_dot_product(p, bitangent);
	uv->u = fmod(uv->u / scale, 1.0);
	if (uv->u < 0.0)
		uv->u += 1.0;
	uv->v = fmod(uv->v / scale, 1.0);
	if (uv->v < 0.0)
		uv->v += 1.0;
}
