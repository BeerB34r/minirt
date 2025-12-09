/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   compute_diffuse.c								  :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/08 13:19:32 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/08 16:46:39 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_mlx.h>

t_vec4	compute_diffuse(t_vec4 light_col, t_shade_input in)
{
	t_vec4	diffuse;
	double	refl;

	diffuse = (t_vec4){0.0f, 0.0f, 0.0f, 1.0f};
	refl = in.mat.diff_reflectivity;
	if (in.dot_ln > 0.0)
	{
		diffuse.x = light_col.x * in.base_colour.x * refl * in.dot_ln;
		diffuse.y = light_col.y * in.base_colour.y * refl * in.dot_ln;
		diffuse.z = light_col.z * in.base_colour.z * refl * in.dot_ln;
	}
	return (diffuse);
}
