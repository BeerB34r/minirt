/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_uv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 11:47:50 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 13:27:55 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <math.h>
#include <minirt_math.h>

void	compute_cyl_cap_uv(t_uv *uv, t_vec3 p, t_vec3 centre, double radius)
{
	t_vec3	diff;

	diff = vec3_sub(p, centre);
	uv->u = 0.5 + vec3_dot_product(diff, uv->t) / (2.0 * radius);
	uv->v = 0.5 + vec3_dot_product(diff, uv->b) / (2.0 * radius);
}

//Potentially add axis to w struct
void	compute_cyl_side_uv(t_uv *uv, t_vec3 p,
		t_vec3 cyl_bottom, t_vec3 cyl_top)
{
	t_vec3	p_rel;
	t_vec3	axis;
	double	height;

	p_rel = vec3_sub(p, cyl_bottom);
	axis = vec3_normalise(vec3_sub(cyl_top, cyl_bottom));
	uv->u = (atan2(vec3_dot_product(p_rel, uv->b),
				vec3_dot_product(p_rel, uv->t)) + PI) / (2.0 * PI);
	height = vec3_length(vec3_sub(cyl_top, cyl_bottom));
	uv->v = vec3_dot_product(vec3_sub(p, cyl_bottom), axis) / height;
}
