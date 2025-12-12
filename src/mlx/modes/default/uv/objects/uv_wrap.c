/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uv_wrap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 16:05:30 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/12/12 10:36:14 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt_declarations.h>

double	wrap1(double w)
{
	w = fmod(w, 1.0f);
	if (w < 0)
		w += 1.0f;
	return (w);
}

t_uv	wrap0(t_uv uv)
{
	t_uv	uv_out;

	uv_out.u = wrap1(uv.u);
	uv_out.v = wrap1(uv.v);
	return (uv_out);
}
