/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_tangents.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 11:27:42 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 11:34:47 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>

void	get_plane_tangents(t_uv *uv, t_vec3 n)
{
	if (fabs(n.x) > fabs(n.y))
		uv->t = vec3_normalise(vec3_cross_product((t_vec3){0, 1, 0}, n));
	else
		uv->t = vec3_normalise(vec3_cross_product((t_vec3){1, 0, 0}, n));
	uv->b = vec3_cross_product(n, uv->t);
}
