/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_side.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 13:38:46 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/09 14:06:31 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>

void	cyl_solve_side(t_line ray,
		const t_rt_element_cylinder *cyl, t_cyl_work *w)
{
	double	sqrt_disc;
	double	t0;
	double	t1;
	double	d;

	sqrt_disc = sqrt(w->disc);
	t0 = (-w->b_coef - sqrt_disc) / (2.0 * w->a_coef);
	t1 = (-w->b_coef + sqrt_disc) / (2.0 * w->a_coef);
	if (t0 > EPSILON)
		w->t_side = t0;
	else if (t1 > EPSILON)
		w->t_side = t1;
	else
		w->t_side = INFINITY;
	if (cyl->height > 0.0 && w->t_side < INFINITY)
	{
		w->p = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, w->t_side));
		d = vec3_dot_product(vec3_sub(w->p, cyl->pos), w->axis);
		if (d < -EPSILON || d > cyl->height + EPSILON)
			w->t_side = INFINITY;
	}
}
