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
	t_vec3	r;
	double	spec_f;

	specular = (t_vec4){0.0f, 0.0f, 0.0f, 1.0f};
	if (in.dot_ln > 0.0f)
	{
		r = vec3_normalise(vec3_sub(
					vec3_scalar_mul(in.n, 2.0f * in.dot_ln), in.l));
		spec_f = powf(fmaxf(vec3_dot_product(r, in.view_dir), 0.0f),
				in.mat.shininess);
		specular = vec3_scalar_mul(
				light_col, in.mat.spec_reflectivity * spec_f);
	}
	return (specular);
}
