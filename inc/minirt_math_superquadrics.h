/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   minirt_math_superquadrics.h                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/10/01 17:07:16 by mde-beer            #+#    #+#           */
/*   Updated: 2025/10/28 19:58:27 by mde-beer            ########   odam.nl   */
/*                                                                            */
/*   —————No norm compliance?——————                                           */
/*   ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                                           */
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

#ifndef MINIRT_MATH_SUPERQUADRICS_H
# define MINIRT_MATH_SUPERQUADRICS_H

# include <minirt_declarations.h>
/*	Naming conventions
 *	sq_.* => functions belonging to the superquadric interface
 *	.*_e_.* => infix for functions belonging to the superellipsoid interface
 *	.*_h1_.* => infix for functions belonging to the superhyperboloids of one
 *	sheet interface
 *	.*_h2_.* => infix for functions belonging to the superhyperboloids of two
 *	sheets interface
 *	.*_t_.* => infix for functions belonging to the supertoroid interface
 *	.*wp_op() => convert point in world-space to object-space
 *	.*wl_ol() => convert line in world-space to object-space
 *	.*_io() => determine wether a point in world-space is inside a given object
 *		return > 1 => outside object
 *		return < 1 => inside object
 *		return = 1 => on the object's surface
 *	.*derivative() => the derivative of the io function, in object space
 *	.*xyz_uv() => converts a given point in world-space on the surface of the
 *	object to angles u,v in terms of the object
 *	.*norm() => returns the unit normal of a point on an objects surface defined
 *	using the angles u,v
 */

t_vec3
	sq_wp_op(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/worldspace_to_objectspace.c
t_line
	sq_wl_ol(
		t_line lw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/worldspace_to_objectspace.c

/*	Superellipsoids */
double
	sq_e_io(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/ellipsoid/e_io_func.c
t_uv
	sq_e_xyz_uv(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/ellipsoid/e_xyz_to_uv.c
t_norm
	sq_e_norm(
		t_uv uv,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/ellipsoid/e_norm.c
double
	sq_e_int(
		t_line lw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/ellipsoid/e_intersection.c
double
	sq_e_derivative(
		t_line l,
		t_vec3 p,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/ellipsoid/e_derivative.c
/*	Superhyperboloids of one sheet */
double
	sq_h1_io(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid1/h1_io_func.c
t_uv
	sq_h1_xyz_uv(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid1/h1_xyz_to_uv.c
t_norm
	sq_h1_norm(
		t_uv uv,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid1/h1_norm.c
double
	sq_h1_int(
		t_line lw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid1/h1_intersection.c
double
	sq_h1_derivative(
		t_line l,
		t_vec3 p,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid1/h1_derivative.c
/*	Superhyperboloids of two sheets */
double
	sq_h2_io(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid2/h2_io_func.c
t_uv
	sq_h2_xyz_uv(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid2/h2_xyz_to_uv.c
t_norm
	sq_h2_norm(
		t_uv uv,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid2/h2_norm.c
double
	sq_h2_int(
		t_line lw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid2/h2_intersection.c
double
	sq_h2_derivative(
		t_line l,
		t_vec3 p,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/hyperboloid2/h2_derivative.c
/*	Supertoroids */
double
	sq_t_io(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/toroid/t_io_func.c
t_uv
	sq_t_xyz_uv(
		t_vec3 pw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/toroid/t_xyz_to_uv.c
t_norm
	sq_t_norm(
		t_uv uv,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/toroid/t_norm.c
double
	sq_t_int(
		t_line lw,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/toroid/t_intersection.c
double
	sq_t_derivative(
		t_line l,
		t_vec3 p,
		struct s_rt_element_superquadric s
		);	// FILE: math/superquadric/toroid/t_derivative.c
#endif // MINIRT_MATH_SUPERQUADRICS_H
