/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 13:47:05 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 13:38:41 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>

static int	cyl_compute_quad(t_line ray,
			const t_rt_element_cylinder *cyl, t_cyl_work *w)
{
	w->axis = vec3_normalise(cyl->axis);
	w->delta = vec3_sub(ray.origin, cyl->pos);
	w->a = vec3_sub(ray.dir, vec3_scalar_mul(
				w->axis, vec3_dot_product(ray.dir, w->axis)));
	w->b = vec3_sub(w->delta, vec3_scalar_mul(
				w->axis, vec3_dot_product(w->delta, w->axis)));
	w->a_coef = vec3_dot_product(w->a, w->a);
	w->b_coef = 2.0 * vec3_dot_product(w->a, w->b);
	w->c_coef = vec3_dot_product(w->b, w->b) - cyl->radius * cyl->radius;
	w->disc = w->b_coef * w->b_coef - 4.0 * w->a_coef * w->c_coef;
	if (w->disc < 0.0)
		return (0);
	else
		return (1);
}

int	cylinder_int(t_line ray, const void *data, double *t, t_uv *uv)
{
	const t_rt_element_cylinder	*cyl = data;
	t_cyl_work					w;

	(void)uv;
	if (!cyl_compute_quad(ray, cyl, &w))
		return (0);
	cyl_solve_side(ray, cyl, &w);
	cyl_solve_caps(ray, cyl, &w);
	w.t_final = fmin(fmin(w.t_side, w.t_bottom), w.t_top);
	if (w.t_final == INFINITY)
		return (0);
	*t = w.t_final;
	return (1);
}
