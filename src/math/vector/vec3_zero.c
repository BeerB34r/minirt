/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_zero.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 14:13:21 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 14:14:30 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>

t_vec3 vec3_zero(void)
{
    t_vec3 v = {0.0f, 0.0f, 0.0f, 0.0f};
    return v;
}