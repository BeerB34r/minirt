/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_side.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/09 13:38:46 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 13:28:47 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>
#include <minirt_mlx.h>

// Potentially move cyl_top and cyl_bottom into w struct
void	cyl_solve_side(t_line ray,
		const t_rt_element_cylinder *cyl, t_cyl_work *w)
{
	double	sqrt_disc;
	double	t0;
	double	t1;
	double	d;
	t_vec3	cyl_top;

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
	cyl_top = vec3_add(cyl->pos, vec3_scalar_mul(w->axis, cyl->height));
	get_cyl_tangents(&w->side_uv, cyl->pos, cyl_top);
	compute_cyl_side_uv(&w->side_uv, w->p, cyl->pos, cyl_top);
}
