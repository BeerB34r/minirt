/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   compute_ambient.c								  :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/08 13:19:36 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/08 16:43:42 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_mlx.h>

t_vec4	compute_ambient(struct s_rt_element_ambient_light ambient,
						t_material material)
{
	float	scale;
	float	ratio;
	t_vec4	mat_col;
	t_vec4	amb_col;
	t_vec4	final_col;

	scale = material.ambi_reflectivity;
	ratio = ambient.ratio;
	mat_col = hex_to_vec4(material.colour.hex);
	amb_col = hex_to_vec4(ambient.colour.hex);
	final_col.x = (mat_col.x * scale + amb_col.x * (1.0f - scale)) * ratio;
	final_col.y = (mat_col.y * scale + amb_col.y * (1.0f - scale)) * ratio;
	final_col.z = (mat_col.z * scale + amb_col.z * (1.0f - scale)) * ratio;
	final_col.w = 1.0f;
	return (final_col);
}
