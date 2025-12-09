/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   reflect.c										  :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/08 12:18:27 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/08 12:19:27 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <minirt_math.h>
#include <minirt_declarations.h>

t_vec3	reflect(t_vec3 I, t_vec3 N)
{
	double	dot_product_in;
	t_vec3	term;

	dot_product_in = vec3_dot_product(I, N);
	term = vec3_scalar_mul(N, 2.0 * dot_product_in);
	return (vec3_sub(I, term));
}