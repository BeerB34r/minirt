/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle_tangents.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 15:24:45 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 15:31:48 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>

void	get_triangle_tangents(t_uv *uv, const t_rt_triangle_uv *tr_uv)
{
	uv->t = vec3_scalar_mul(
			vec3_sub(
				vec3_scalar_mul(tr_uv->e1, tr_uv->dv2),
				vec3_scalar_mul(tr_uv->e2, tr_uv->dv1)),
			tr_uv->r);
	uv->b = vec3_scalar_mul(
			vec3_sub(
				vec3_scalar_mul(tr_uv->e2, tr_uv->du1),
				vec3_scalar_mul(tr_uv->e1, tr_uv->du2)),
			tr_uv->r);
	uv->t = vec3_normalise(uv->t);
	uv->b = vec3_normalise(uv->b);
}
