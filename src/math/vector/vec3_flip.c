/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_flip.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 13:23:36 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/09 14:00:40 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>

t_vec3	vec3_flip(t_vec3 v)
{
	t_vec3	out;

	out.x = -v.x;
	out.y = -v.y;
	out.z = -v.z;
	return (out);
}
