/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_tangents.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 13:00:11 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 13:28:07 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <math.h>

void	get_cyl_tangents(t_uv *uv, t_vec3 cyl_bottom, t_vec3 cyl_top)
{
	t_vec3	axis;
	t_vec3	ref;

	axis = vec3_normalise(vec3_sub(cyl_top, cyl_bottom));
	ref = (t_vec3){1, 0, 0};
	if (fabs(vec3_dot_product(axis, ref)) > 0.99)
		ref = (t_vec3){0, 0, 1};
	uv->t = vec3_normalise(vec3_cross_product(ref, axis));
	uv->b = vec3_cross_product(axis, uv->t);
}
