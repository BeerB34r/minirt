/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   triangle.c										 :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/03 16:58:17 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/04 14:34:26 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>
#include <minirt_mlx.h>

static int	tri_step_det(t_line ray,
				const t_rt_element_triangle *tri, t_tri_work *w)
{
	w->e1 = vec3_sub(tri->v2, tri->v1);
	w->e2 = vec3_sub(tri->v3, tri->v1);
	w->p = vec3_cross_product(ray.dir, w->e2);
	w->det = vec3_dot_product(w->e1, w->p);
	if (fabs(w->det) < EPSILON)
		return (0);
	w->inv_det = 1.0 / w->det;
	return (1);
}

static int	tri_step_uv(t_line ray,
		const t_rt_element_triangle *tri, t_tri_work *w)
{
	t_vec3	t;

	t = vec3_sub(ray.origin, tri->v1);
	w->u = vec3_dot_product(t, w->p) * w->inv_det;
	if (w->u < 0.0 || w->u > 1.0)
		return (0);
	w->q = vec3_cross_product(t, w->e1);
	w->v = vec3_dot_product(ray.dir, w->q) * w->inv_det;
	if (w->v < 0.0 || w->u + w->v > 1.0)
		return (0);
	return (1);
}

static int	tri_step_t(t_tri_work *w, double *t)
{
	double	hit;

	hit = vec3_dot_product(w->e2, w->q) * w->inv_det;
	if (hit < EPSILON)
		return (0);
	*t = hit;
	return (1);
}

int	triangle_int(t_line ray, const void *data, double *t, t_uv *uv)
{
	const t_rt_element_triangle	*tri = data;
	t_tri_work					w;

	(void)uv;
	if (!tri_step_det(ray, tri, &w))
		return (0);
	if (!tri_step_uv(ray, tri, &w))
		return (0);
	get_triangle_uv(uv, &tri->tr_uv, w);
	get_triangle_tangents(uv, &tri->tr_uv);
	return (tri_step_t(&w, t));
}
