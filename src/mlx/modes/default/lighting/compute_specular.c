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

t_vec4	compute_specular(t_vec4 light_col, t_material *material,
						t_vec3 N, t_vec3 V, t_vec3 L, double dot_product_ln)
{
	t_vec4	specular;
	t_vec3	r;
	double	dot_product_rv;
	double	spec_f;

	specular = (t_vec4){0.0f, 0.0f, 0.0f, 1.0f};
	if (dot_product_ln > 0.0f)
	{
		r = vec3_normalise(vec3_sub(
					vec3_scalar_mul(N, 2.0f * dot_product_ln), L));
		dot_product_rv = fmaxf(vec3_dot_product(r, V), 0.0f);
		spec_f = powf(dot_product_rv, material->shininess);
		specular = vec3_scalar_mul(
				light_col, material->spec_reflectivity * spec_f);
	}
	return (specular);
}
