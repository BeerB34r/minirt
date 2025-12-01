// incorporate this.

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>
#include <stdio.h>

double triangle_int(t_line line, struct s_rt_element_triangle tri) {
	const double EPSILON = 1e-8; // potentially make this a universal constant
	t_vec3 E1 = vec3_sub(tri.v2, tri.v1);
	t_vec3 E2 = vec3_sub(tri.v3, tri.v1);
	t_vec3 P = vec3_cross_product(line.normal, E2);
	double det = vec3_dot_product(E1, P);

	if (fabs(det) < EPSILON) {
		return (NAN);
	}
    double inv_det = 1.0 / det;
    t_vec3 T = vec3_sub(line.origin, tri.v1);
    double u = vec3_dot_product(T, P) * inv_det;
    if (u < 0.0 || u > 1.0)
        return (NAN);

    t_vec3 Q = vec3_cross_product(T, E1);
    double v = vec3_dot_product(line.normal, Q) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return (NAN);

    double res = vec3_dot_product(E2, Q) * inv_det;
    if (res < 0) 
        return (NAN);
    return (res);
}

