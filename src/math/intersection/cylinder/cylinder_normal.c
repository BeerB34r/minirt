/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   cylinder_normal.c								  :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/09 13:38:48 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/09 13:53:49 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>

static int	cyl_normal_bottom(t_rt_element_cylinder cyl,
			t_vec3 int_point, t_cyl_work *w, t_vec3 *out)
{
	if (w->d < EPSILON)
	{
		w->v = vec3_sub(int_point, cyl.pos);
		if (vec3_dot_product(w->v, w->v) <= cyl.radius * cyl.radius + EPSILON)
		{
			*out = vec3_scalar_mul(w->axis, -1);
			return (1);
		}
	}
	return (0);
}

static int	cyl_normal_top(t_rt_element_cylinder cyl,
			t_vec3 int_point, t_cyl_work *w, t_vec3 *out)
{
	if (w->d > cyl.height - EPSILON)
	{
		w->p = vec3_add(cyl.pos, vec3_scalar_mul(w->axis, cyl.height));
		w->v = vec3_sub(int_point, w->p);
		if (vec3_dot_product(w->v, w->v) <= cyl.radius * cyl.radius + EPSILON)
		{
			*out = w->axis;
			return (1);
		}
	}
	return (0);
}

static t_vec3	cyl_normal_side(t_cyl_work *w)
{
	t_vec3	proj;

	proj = vec3_scalar_mul(w->axis, w->d);
	return (vec3_normalise(vec3_sub(w->delta, proj)));
}

t_vec3	cylinder_normal(t_rt_element_cylinder cyl, t_vec3 int_point)
{
	t_cyl_work	w;
	t_vec3		out;

	w.axis = vec3_normalise(cyl.axis);
	w.delta = vec3_sub(int_point, cyl.pos);
	w.d = vec3_dot_product(w.delta, w.axis);
	if (cyl_normal_bottom(cyl, int_point, &w, &out))
		return (out);
	if (cyl_normal_top(cyl, int_point, &w, &out))
		return (out);
	return (cyl_normal_side(&w));
}
