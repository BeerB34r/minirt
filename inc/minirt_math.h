/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt_math.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/23 15:38:31 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/11 11:31:26 by alkuijte      ########   odam.nl         */
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
# define EPSILON 1.0e-6
# define PI 3.1415926535f

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

// Intersections
int		
	sphere_int(
		t_line ray,
		const void *type,
		double *t,
		t_uv *uv
		);
int		
	plane_int(
		t_line ray,
		const void *type,
		double *t,
		t_uv *uv
		);
int		
	triangle_int(
		t_line ray,
		const void *type,
		double *t,
		t_uv *uv
		);
int		
	cylinder_int(
		t_line ray,
		const void *type,
		double *t,
		t_uv *uv
		);
t_vec3	
	cylinder_normal(
		struct s_rt_element_cylinder cyl,
		t_vec3 int_point
		);
t_vec3	
	reflect(
		t_vec3 I,
		t_vec3 N
		);

t_vec3	
	vec3_flip(
		t_vec3 v
		);
void	
	vec3_add_inplace(
		t_vec3 *a,
		t_vec3 b
		);
t_vec3	
	vec3_zero(
		);
void	
	cyl_solve_side(
		t_line ray,
		const t_rt_element_cylinder *cyl,
		t_cyl_work *w
		);
t_vec3	
	cylinder_normal(
		struct s_rt_element_cylinder cyl,
		t_vec3 int_point
		);
void	
	cyl_solve_caps(
		t_line ray,
		const t_rt_element_cylinder *cyl,
		t_cyl_work *w
		);
t_vec3	
	get_local_point(
		t_line ray,
		double t,
		t_vec3 pos
		);
void	
	get_sphere_tangents(
		t_uv *uv,
		t_vec3 n
		);
void	
	get_plane_tangents(
		t_uv *uv,
		t_vec3 n
		);
#endif // MINIRT_MATH_H
