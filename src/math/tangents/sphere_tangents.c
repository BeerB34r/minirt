/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_tangents.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 10:48:49 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 11:34:54 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>

t_vec3	compute_tangent_direction(double theta, double phi)
{
	t_vec3	tangent_direction;

	tangent_direction.x = cos(phi) * -sin(theta);
	tangent_direction.y = 0;
	tangent_direction.z = cos(phi) * cos(theta);
	return (tangent_direction);
}

void	get_sphere_tangents(t_uv *uv, t_vec3 n)
{
	double	theta;
	double	phi;
	t_vec3	t;

	theta = 2.0f * PI * (uv->u - 0.5f);
	phi = PI * (uv->v - 0.5f);
	t = compute_tangent_direction(theta, phi);
	t = vec3_sub(t, (vec3_scalar_mul(n, vec3_dot_product(n, t))));
	uv->t = vec3_normalise(t);
	uv->b = vec3_cross_product(n, t);
}
