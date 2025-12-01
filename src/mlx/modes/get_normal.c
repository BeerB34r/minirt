/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_normal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 16:40:27 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/01 16:52:47 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>

t_vec3 get_normal(struct s_rt_element obj, t_vec3 point) {
	if (obj.type == SPHERE) {
        return vec3_normalise(vec3_sub(point, obj.sphere.pos));
	} else if (obj.type == SUPERQUADRIC) {
		return sq_norm(sq_xyz_uv(point, obj.superquadric), obj.superquadric);
    } else if (obj.type == PLANE) {
		return (obj.plane.normal);
	} else if (obj.type == TRIANGLE) {
		return (obj.triangle.normal);
	} else if (obj.type == CYLINDER) {
		return (cylinder_normal(obj.cylinder, point));
	}
    return (t_vec3){0,0,1}; // just in case
}