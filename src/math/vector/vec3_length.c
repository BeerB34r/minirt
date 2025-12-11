/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_length.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 12:05:55 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/11 13:28:13 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_declarations.h>

double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
