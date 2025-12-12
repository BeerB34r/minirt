/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   default.c										  :+:	:+:			*/
/*													 +:+					*/
/*   By: alkuijte <alkuijte@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/12/01 16:19:52 by alkuijte	  #+#	#+#				 */
/*   Updated: 2025/12/08 18:10:14 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

t_trace_work	create_trace_work(struct s_rt_scene *scene,
								t_line ray, int depth)
{
	t_trace_work	w;

	w.scene = scene;
	w.ray = ray;
	w.depth = depth;
	w.bg = hex_to_vec4(PIXEL_BG);
	w.hit.t = 0.0f;
	return (w);
}

t_vec4	trace_ray(t_trace_work *w);

static void	handle_reflection(t_trace_work *w)
{
	t_vec3			i;
	t_vec3			r;
	t_line			reflected_ray;
	t_trace_work	w_refl;
	t_vec4			refl_col;

	i = vec3_normalise(w->ray.dir);
	r = reflect(i, w->hit.normal);
	reflected_ray.origin = vec3_add(
			w->hit.point, vec3_scalar_mul(w->hit.normal, EPSILON));
	reflected_ray.dir = r;
	w_refl = create_trace_work(w->scene, reflected_ray, w->depth + 1);
	refl_col = trace_ray(&w_refl);
	w->colour = blend_colour(
			w->colour, refl_col, w->hit.obj->material.abso_reflectivity);
}

t_vec4	trace_ray(t_trace_work *w)
{
	if (w->depth >= MAX_DEPTH)
		return (w->bg);
	if (!find_closest_intersection(w->scene, w->ray, &w->hit))
		return (w->bg);
	w->hit.ray = w->ray;
	w->hit.point = vec3_add(
			w->ray.origin, vec3_scalar_mul(w->ray.dir, w->hit.t));
	w->hit.normal = get_normal(*w->hit.obj, w->hit.point);
	if (vec3_dot_product(w->ray.dir, w->hit.normal) > 0)
		w->hit.normal = vec3_scalar_mul(w->hit.normal, -1);
	w->colour = shade(w->scene, &w->hit);
	if (w->hit.obj->material.abso_reflectivity > 0.0f)
		handle_reflection(w);
	return (w->colour);
}

void	default_colour(struct s_mode_func_params p,
					t_line	angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
					struct	s_rgba *colour)
{
	t_trace_work	w;
	t_vec4			c;

	w = create_trace_work(p.scene, angles[p.x][p.y], 0);
	c = trace_ray(&w);
	c = vec3_scalar_mul(c, EXPOSURE);
	clamp_colour(&c);
	colour->hex = vec4_to_hex(c);
}
