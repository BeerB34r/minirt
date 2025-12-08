/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_add_inplace.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 13:25:14 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 13:26:39 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>

void	vec3_add_inplace(t_vec3 *a, t_vec3 b)
{
	a->x += b.x;
	a->y += b.y;
	a->z += b.z;
}