/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   cylinder.c										 :+:	:+:			*/
/*													 +:+					*/
/*   By: mde-beer <mde-beer@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/09/23 19:08:39 by mde-beer	  #+#	#+#				 */
/*   Updated: 2025/12/04 14:34:16 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇										   */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀										   */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀										   */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ——————————————————————————————										   */
/* ************************************************************************** */

#include <math.h>
#include <minirt_math.h>
#include <minirt_declarations.h>
#include <stdio.h>

t_vec3	cylinder_normal(struct s_rt_element_cylinder cyl, t_vec3 int_point)
{
	t_vec3	axis;
	t_vec3	delta;
	t_vec3	v;
	t_vec3	cap_top;
	t_vec3	proj;
	double	d;

	axis = vec3_normalise(cyl.axis);
	delta = vec3_sub(int_point, cyl.pos);
	d = vec3_dot_product(delta, axis);
	if (d < EPSILON)
	{
		v = vec3_sub(int_point, cyl.pos);
		if (vec3_dot_product(v, v) <= cyl.radius * cyl.radius + EPSILON)
			return (vec3_scalar_mul(axis, -1));
	}
	if (d > cyl.height - EPSILON)
	{
		cap_top = vec3_add(cyl.pos, vec3_scalar_mul(axis, cyl.height));
		v = vec3_sub(int_point, cap_top);
		if (vec3_dot_product(v, v) <= cyl.radius * cyl.radius + EPSILON)
			return (axis);
	}
	proj = vec3_scalar_mul(axis, d);
	return (vec3_normalise(vec3_sub(delta, proj)));
}

int	cylinder_int(t_line ray, const void *data, double *t)
{
	const struct s_rt_element_cylinder	*cyl = (const struct s_rt_element_cylinder *)data;
	t_vec3								axis;
	t_vec3								delta;
	t_vec3								a;
	t_vec3								b;
	t_vec3								cap_bottom;
	t_vec3								cap_top;
	t_vec3								P;
	t_vec3								v;
	double								A;
	double								B;
	double								C;
	double								disc;
	double								sqrt_disc;
	double								t0;
	double								t1;
	double								t_side;
	double								t_bottom;
	double								t_top;
	double								d;
	double								denom;
	double								t_cap;
	double								t_final;

	if (!data)
	{
		fprintf(stderr, "cylinder_int called with NULL data\n");
		return (0);
	}
	axis = vec3_normalise(cyl->axis);
	delta = vec3_sub(ray.origin, cyl->pos);
	a = vec3_sub(ray.dir, vec3_scalar_mul(axis, vec3_dot_product(ray.dir, axis)));
	b = vec3_sub(delta, vec3_scalar_mul(axis, vec3_dot_product(delta, axis)));
	A = vec3_dot_product(a, a);
	B = 2.0 * vec3_dot_product(a, b);
	C = vec3_dot_product(b, b) - cyl->radius * cyl->radius;
	disc = B * B - 4.0 * A * C;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	t0 = (-B - sqrt_disc) / (2.0 * A);
	t1 = (-B + sqrt_disc) / (2.0 * A);
	t_side = (t0 > EPSILON) ? t0 : ((t1 > EPSILON) ? t1 : INFINITY);
	if (cyl->height > 0.0 && t_side < INFINITY)
	{
		P = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, t_side));
		d = vec3_dot_product(vec3_sub(P, cyl->pos), axis);
		if (d < -EPSILON || d > cyl->height + EPSILON)
			t_side = INFINITY;
	}
	t_bottom = INFINITY;
	t_top = INFINITY;
	cap_bottom = cyl->pos;
	cap_top = vec3_add(cyl->pos, vec3_scalar_mul(axis, cyl->height));
	denom = vec3_dot_product(ray.dir, axis);
	if (fabs(denom) > EPSILON)
	{
		t_cap = vec3_dot_product(vec3_sub(cap_bottom, ray.origin), axis) / denom;
		if (t_cap > EPSILON)
		{
			P = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, t_cap));
			v = vec3_sub(P, cap_bottom);
			if (vec3_dot_product(v, v) <= cyl->radius * cyl->radius)
				t_bottom = t_cap;
		}
		t_cap = vec3_dot_product(vec3_sub(cap_top, ray.origin), axis) / denom;
		if (t_cap > EPSILON)
		{
			P = vec3_add(ray.origin, vec3_scalar_mul(ray.dir, t_cap));
			v = vec3_sub(P, cap_top);
			if (vec3_dot_product(v, v) <= cyl->radius * cyl->radius)
				t_top = t_cap;
		}
	}
	t_final = fmin(fmin(t_side, t_bottom), t_top);
	if (t_final == INFINITY)
		return (0);
	*t = t_final;
	return (1);
}
