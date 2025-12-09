/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_caps.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 13:43:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/09 14:04:26 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>

static void	cyl_solve_bottom_cap(t_line ray,
			const t_rt_element_cylinder *cyl, t_cyl_work *w)
{
	t_vec3	cap_bottom;

	cap_bottom = cyl->pos;
	w->t_bottom = INFINITY;
	w->t_cap = vec3_dot_product(
			vec3_sub(cap_bottom, ray.origin), w->axis) / w->denom;
	if (w->t_cap > EPSILON)
	{
		w->p = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, w->t_cap));
		w->v = vec3_sub(w->p, cap_bottom);
		if (vec3_dot_product(w->v, w->v) <= cyl->radius * cyl->radius)
			w->t_bottom = w->t_cap;
	}
}

static void	cyl_solve_top_cap(t_line ray,
		const t_rt_element_cylinder *cyl, t_cyl_work *w)
{
	t_vec3	cap_top;

	cap_top = vec3_add(cyl->pos, vec3_scalar_mul(w->axis, cyl->height));
	w->t_top = INFINITY;
	w->t_cap = vec3_dot_product(vec3_sub(
				cap_top, ray.origin), w->axis) / w->denom;
	if (w->t_cap > EPSILON)
	{
		w->p = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, w->t_cap));
		w->v = vec3_sub(w->p, cap_top);
		if (vec3_dot_product(w->v, w->v) <= cyl->radius * cyl->radius)
			w->t_top = w->t_cap;
	}
}

void	cyl_solve_caps(t_line ray,
			const t_rt_element_cylinder *cyl, t_cyl_work *w)
{
	w->denom = vec3_dot_product(ray.dir, w->axis);
	if (fabs(w->denom) > EPSILON)
	{
		cyl_solve_bottom_cap(ray, cyl, w);
		cyl_solve_top_cap(ray, cyl, w);
	}
}
