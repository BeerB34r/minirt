/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   sphere.c										   :+:	:+:			*/
/*													 +:+					*/
/*   By: mde-beer <mde-beer@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/09/23 16:13:08 by mde-beer	  #+#	#+#				 */
/*   Updated: 2025/12/04 14:34:21 by alkuijte	  ########   odam.nl		 */
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

int	sphere_int(t_line ray, const void *data, double *t)
{
	const struct s_rt_element_sphere	*sp = (const struct s_rt_element_sphere *)data;
	t_vec3								l;
	double								b;
	double								c_term;
	double								disc;
	double								sqrt_disc;
	double								t0;
	double								t1;
	double								t_final;

	if (!data)
	{
		fprintf(stderr, "sphere_int called with NULL data\n");
		return (0);
	}
	l = vec3_sub(ray.origin, sp->pos);
	b = vec3_dot_product(ray.dir, l);
	c_term = vec3_dot_product(l, l) - sp->radius * sp->radius;
	disc = b * b - c_term;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	t0 = -b - sqrt_disc;
	t1 = -b + sqrt_disc;
	if (t0 > EPSILON)
		t_final = t0;
	else if (t1 > EPSILON)
		t_final = t1;
	else
		return (0);
	*t = t_final;
	return (1);
}
