/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/23 19:08:39 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/03 16:58:02 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                                           */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                                           */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀                                           */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ——————————————————————————————                                           */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>
#include <stdio.h>


t_vec3 cylinder_normal(struct s_rt_element_cylinder cyl, t_vec3 int_point) {
    t_vec3 axis = vec3_normalise(cyl.axis);
    t_vec3 delta = vec3_sub(int_point, cyl.pos);
    double d = vec3_dot_product(delta, axis);

    if (d < EPSILON) {
        t_vec3 v = vec3_sub(int_point, cyl.pos);
        if (vec3_dot_product(v, v) <= cyl.radius * cyl.radius + EPSILON) {
            return vec3_scalar_mul(axis, -1);
		} 
    }

    if (d > cyl.height - EPSILON) {
        t_vec3 cap_top = vec3_add(cyl.pos, vec3_scalar_mul(axis, cyl.height));
        t_vec3 v = vec3_sub(int_point, cap_top);
        if (vec3_dot_product(v, v) <= cyl.radius * cyl.radius + EPSILON) {
            return axis;
        }
    }

    t_vec3 proj = vec3_scalar_mul(axis, d);
    return vec3_normalise(vec3_sub(delta, proj));
}



double cylinder_int(t_line line, struct s_rt_element_cylinder cyl)
{
    t_vec3 axis = vec3_normalise(cyl.axis);

    t_vec3 delta = vec3_sub(line.origin, cyl.pos);

    t_vec3 a = vec3_sub(line.dir, vec3_scalar_mul(axis, vec3_dot_product(line.dir, axis)));
    t_vec3 b = vec3_sub(delta, vec3_scalar_mul(axis, vec3_dot_product(delta, axis)));

    double A = vec3_dot_product(a, a);
    double B = 2.0 * vec3_dot_product(a, b);
    double C = vec3_dot_product(b, b) - cyl.radius * cyl.radius;

    double disc = B * B - 4.0 * A * C;
    if (disc < 0.0) {
        return NAN; 
    }

    double sqrt_disc = sqrt(disc);
    double t0 = (-B - sqrt_disc) / (2.0 * A);
    double t1 = (-B + sqrt_disc) / (2.0 * A);

    double t_side = (t0 > EPSILON) ? t0 : ((t1 > EPSILON) ? t1 : NAN);

    t_vec3 P = vec3_add(line.origin, vec3_scalar_mul(line.dir, t_side));

    if (cyl.height > 0.0) {
        double d = vec3_dot_product(vec3_sub(P, cyl.pos), axis);
        if (d < -EPSILON || d > cyl.height + EPSILON) {
            t_side = NAN;
        }
    }
    double t_bottom = NAN;
	t_vec3 cap_bottom = cyl.pos;
	double denom = vec3_dot_product(line.dir, axis);
	if (fabs(denom) > EPSILON) {
 	   double t_cap = vec3_dot_product(vec3_sub(cap_bottom, line.origin), axis) / denom;
  	  if (t_cap > EPSILON) {
  	      t_vec3 P = vec3_add(line.origin, vec3_scalar_mul(line.dir, t_cap));
   	     t_vec3 v = vec3_sub(P, cap_bottom);
   	     if (vec3_dot_product(v, v) <= cyl.radius * cyl.radius) t_bottom = t_cap;
  	  }
	}
    t_vec3 cap_top = vec3_add(cyl.pos, vec3_scalar_mul(axis, cyl.height));
    denom = vec3_dot_product(line.dir, axis);
    double t_top = NAN;
    if (fabs(denom) > EPSILON) {
        double t_cap = vec3_dot_product(vec3_sub(cap_top, line.origin), axis) / denom;
        if (t_cap > EPSILON) {
            t_vec3 P = vec3_add(line.origin, vec3_scalar_mul(line.dir, t_cap));
            t_vec3 v = vec3_sub(P, cap_top);
            if (vec3_dot_product(v, v) <= cyl.radius * cyl.radius) t_top = t_cap;
        }
    }


    double t_final = NAN;
    if (!isnan(t_side)) t_final = t_side;
    if (!isnan(t_bottom) && (isnan(t_final) || t_bottom < t_final)) t_final = t_bottom;
    if (!isnan(t_top) && (isnan(t_final) || t_top < t_final)) t_final = t_top;

    return t_final;
}


