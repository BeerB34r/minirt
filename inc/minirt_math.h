/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt_math.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/23 15:38:31 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/03 16:57:56 by alkuijte      ########   odam.nl         */
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

#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# include <minirt_declarations.h> // function prototypes

//	//	mathematical constants (for some fucking reason???????)
# define EPSILON 1e-6;

//	//	trigonometric interface (for some fucking reason????)
double	
	sec(
		double theta
		);	// FILE: math/sec.c
double	
	asec(
		double theta
		);	// FILE: math/sec.c
//	//	vec3 interface
int		
	vec3_is_normalised(
		t_vec3 vector
		);	// FILE: math/vec3_is_normalised.c
double	
	vec3_magnitude(
		t_vec3 vector
		);	// FILE: math/vec3_magnitude.c
t_norm	
	vec3_normalise(
		t_vec3 vector
		);	// FILE: math/vec3_normalise.c
t_vec3	
	vec3_add(
		t_vec3 a,
		t_vec3 b
		);	// FILE: math/vec3_add.c
t_vec3	
	vec3_sub(
		t_vec3 a,
		t_vec3 b
		);	// FILE: math/vec3_sub.c
t_vec3	
	vec3_scalar_mul(
		t_vec3 a,
		double r
		);	// FILE: math/vec3_scalar_mul.c
double	
	vec3_dot_product(
		t_vec3 a,
		t_vec3 b
		);	// FILE: math/vec3_dot_product.c
t_vec3	
	vec3_cross_product(
		t_vec3 a,
		t_vec3 b
		);	// FILE: math/vec3_cross_product.c
double	
	vec3_box_product(
		t_vec3 a,
		t_vec3 b,
		t_vec3 c
		);	// FILE: math/vec3_box_product.c

//	//	line interface
t_vec3	
	l_t(
		t_line l,
		double t
		);	// FILE: math/line_l_t.c
//	//	line intersection functions
//	returns a real number d equal to the distance from the lines origin to the
//	point of intersection, or NAN if there is no intersection
double	
	closest_sphere_intersection(
		t_element object,
		t_line line
		);	// FILE: math/intersection/sphere.c
double	
	closest_plane_intersection(
		t_element object,
		t_line line
		);	// FILE: math/intersection/plane.c
double	
	closest_cylinder_intersection(
		t_element object,
		t_line line
		);	// FILE: math/intersection/cylinder.c
double	
	closest_superquadric_intersection(
		t_element object,
		t_line line
		);	// FILE: math/intersection/superquadric.c
double	
	closest_triangle_intersection(
		t_element object,
		t_line line
		);	// FILE: math/intersection/triangle.c
double	
	closest_stlfile_intersection(
		t_element object,
		t_line line
		);	// FILE: math/intersection/stlfile.c

double sphere_int(t_line line, struct s_rt_element_sphere object);
double plane_int(t_line line, struct s_rt_element_plane object);
double triangle_int(t_line line, struct s_rt_element_triangle object);
double	cylinder_int(t_line line, struct s_rt_element_cylinder cyl);
t_vec3 cylinder_normal(struct s_rt_element_cylinder cyl, t_vec3 int_point);
#endif // MINIRT_MATH_H
