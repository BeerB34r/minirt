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
						float mat_ambi_refl)
{
	t_vec4	amb_col;
	t_vec4	final_col;

	amb_col = hex_to_vec4(ambient.colour.hex);
	final_col.x = amb_col.x * mat_ambi_refl;
	final_col.y = amb_col.y * mat_ambi_refl;
	final_col.z = amb_col.z * mat_ambi_refl;
	final_col.w = 1.0f;
	return (final_col);
}
