/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_uv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 11:21:12 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 13:04:25 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_math.h>
#include <math.h>

void	get_sphere_uv(double *u, double *v, t_vec3 p)
{
	*u = 0.5 + (atan2(p.z, p.x) / (PI * 2.0f));
	*v = 0.5 + (asin(p.y) / PI);
}
