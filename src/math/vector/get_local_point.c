/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_local_point.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/10 14:01:28 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/10 15:31:53 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_math.h>

t_vec3	get_local_point(t_line ray, double t, t_vec3 pos)
{
	return (vec3_sub(vec3_add(ray.origin, vec3_scalar_mul(ray.dir, t)), pos));
}
