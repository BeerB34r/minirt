/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compute_diffuse.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 13:19:32 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/08 15:37:00 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_mlx.h>




t_vec4 compute_diffuse(t_vec4 light_col, t_vec4 material_col, double diff_refl, double dotLN)
{
    t_vec4 diffuse = {0.0f, 0.0f, 0.0f, 1.0f}; 
    if (dotLN > 0.0)
    {
        diffuse.x = light_col.x * material_col.x * diff_refl * dotLN;
        diffuse.y = light_col.y * material_col.y * diff_refl * dotLN;
        diffuse.z = light_col.z * material_col.z * diff_refl * dotLN;
    }
    return diffuse;
}