/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 16:58:17 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/04 14:34:26 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>
#include <stdio.h>


int triangle_int(t_line ray, const void *data, double *t)
{
    if (!data) {
        fprintf(stderr, "triangle_int called with NULL data\n");
        return 0;
    }
    const struct s_rt_element_triangle *tri = (const struct s_rt_element_triangle *)data;

    t_vec3 E1 = vec3_sub(tri->v2, tri->v1);
    t_vec3 E2 = vec3_sub(tri->v3, tri->v1);
    t_vec3 P = vec3_cross_product(ray.dir, E2);
    double det = vec3_dot_product(E1, P);

    if (fabs(det) < EPSILON)
        return 0;

    double inv_det = 1.0 / det;
    t_vec3 T = vec3_sub(ray.origin, tri->v1);
    double u = vec3_dot_product(T, P) * inv_det;
    if (u < 0.0 || u > 1.0)
        return 0;

    t_vec3 Q = vec3_cross_product(T, E1);
    double v = vec3_dot_product(ray.dir, Q) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return 0;

    double res = vec3_dot_product(E2, Q) * inv_det;
    if (res < EPSILON)
        return 0;
    *t = res;
    return 1;
}

