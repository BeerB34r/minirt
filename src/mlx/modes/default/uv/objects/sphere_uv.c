/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_uv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 11:21:12 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 13:15:53 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_math.h>
#include <math.h>

void	get_sphere_uv(double *u, double *v, t_vec3 p,
		t_rt_element_sphere sphere)
{
	t_vec3	local_p;

	local_p = vec3_sub(p, sphere.pos);
	*u = 0.5 + (atan2(local_p.z, local_p.x) / (PI * 2.0f));
	*v = 0.5 + (asin(local_p.y / sphere.radius) / PI);
}
