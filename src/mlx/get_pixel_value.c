/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   get_pixel_value.c								  :+:	:+:			*/
/*													 +:+					*/
/*   By: mde-beer <mde-beer@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/11/05 19:11:13 by mde-beer	  #+#	#+#				 */
/*   Updated: 2025/12/08 18:11:26 by alkuijte	  ########   odam.nl		 */
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
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>

static inline int	check_intersection(const struct s_rt_element *obj,
									t_line ray, double *t)
{
	if (!obj->intersect || !obj->data)
		return (0);
	return (obj->intersect(ray, obj->data, t));
}

static const struct s_camera_mode	g_modes[] = {
{HIT_OR_MISS, hit_or_miss_colour},
{SURFACE_NORMAL, surface_normal_colour},
{DEFAULT, default_colour}
};

int	find_closest_intersection(t_scene *scene, t_line ray, t_hit *out_hit)
{
	double			t_min;
	double			t;
	t_element		*hit_obj;
	unsigned int	i;

	t_min = INFINITY;
	hit_obj = NULL;
	i = -1;
	while (++i < scene->element_count)
	{
		if (check_intersection(&scene->elements[i], ray, &t))
		{
			if (t >= 0 && t < t_min)
			{
				t_min = t;
				hit_obj = &scene->elements[i];
			}
		}
	}
	if (!hit_obj)
		return (0);
	out_hit->obj = hit_obj;
	out_hit->t = t_min;
	return (1);
}

void	get_pixel_value(struct s_get_pixel_params p,
					t_line rays[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
					struct s_rgba *out)
{
	t_hit	hit;

	if (!find_closest_intersection(p.scene, rays[p.x][p.y], &hit))
	{
		out->hex = PIXEL_BG;
		return ;
	}
	g_modes[p.mode].func((struct s_mode_func_params){
		.scene = p.scene,
		.hit = hit,
		.x = p.x,
		.y = p.y
	}, rays, out);
}