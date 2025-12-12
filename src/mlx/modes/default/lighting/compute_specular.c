/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   compute_specular.c								 :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/08 13:19:38 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/08 14:47:30 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_mlx.h>
#include <math.h>

t_vec4	compute_specular(t_vec4 light_col, t_shade_input in)
{
	t_vec4	specular;
	double	t;
	double	refl;

	specular = (t_vec4){0.0f, 0.0f, 0.0f, 1.0f};
	refl = in.mat.spec_reflectivity;
	t_vec3 r = vec3_normalise(reflect(vec3_scalar_mul(in.l, -1.0f), in.n));

	t = pow(
			fmaxf(
				vec3_dot_product(
					r,
					in.view_dir),
				0.0f),
			in.mat.shininess);
	specular.x = refl * light_col.x * t;
	specular.y = refl * light_col.y * t;
	specular.z = refl * light_col.z * t;
	return (specular);
}
