/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   triangle.c										 :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/03 16:58:17 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/04 14:34:26 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>
#include <stdio.h>

int	triangle_int(t_line ray, const void *data, double *t)
{
	const t_rt_element_triangle	*tri = (const t_rt_element_triangle *)data;
	double								det;
	double								inv_det;
	double								u;
	double								v;
	double								res;
	t_vec3								e1;
	t_vec3								e2;
	t_vec3								p;
	t_vec3								q;

	if (!data)
	{
		fprintf(stderr, "triangle_int called with NULL data\n");
		return (0);
	}
	e1 = vec3_sub(tri->v2, tri->v1);
	e2 = vec3_sub(tri->v3, tri->v1);
	p = vec3_cross_product(ray.dir, e2);
	det = vec3_dot_product(e1, p);
	if (fabs(det) < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	t_vec3 T = vec3_sub(ray.origin, tri->v1);
	u = vec3_dot_product(T, p) * inv_det;
	if (u < 0.0 || u > 1.0)
		return (0);
	q = vec3_cross_product(T, e1);
	v = vec3_dot_product(ray.dir, q) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return (0);
	res = vec3_dot_product(e2, q) * inv_det;
	if (res < EPSILON)
		return (0);
	*t = res;
	return (1);
}
