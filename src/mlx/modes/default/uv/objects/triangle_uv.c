/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle_uv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 14:48:35 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 15:16:11 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <math.h>

void	get_triangle_uv(t_uv *uv, t_rt_triangle_uv *t, t_tri_work w)
{
	double	max_u;
	double	max_v;

	max_u = fmax(fmax(t->uv1.x, t->uv2.x), t->uv3.x);
	max_v = fmax(fmax(t->uv1.y, t->uv2.y), t->uv3.y);
	uv->u = t->uv1.x * (1.0 - w.u - w.v) + t->uv2.x * w.u + t->uv3.x * w.v;
	uv->v = t->uv1.y * (1.0 - w.u - w.v) + t->uv2.y * w.u + t->uv3.y * w.v;
	uv->u /= max_u;
	uv->v /= max_v;
}
