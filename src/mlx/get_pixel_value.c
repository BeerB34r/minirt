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

int	check_intersection(const struct s_rt_element *obj,
									t_line ray, double *t, t_uv *uv)
{
	if (!obj->intersect || !obj->data)
		return (0);
	return (obj->intersect(ray, obj->data, t, uv));
}

static const struct s_camera_mode	g_modes[] = {
{HIT_OR_MISS, hit_or_miss_colour},
{SURFACE_NORMAL, surface_normal_colour},
{DEFAULT, default_colour}
};

int	find_closest_intersection(t_scene *scene, t_line ray, t_hit *out_hit)
{
	double			t;
	t_uv			uv;
	unsigned int	i;

	out_hit->t = INFINITY;
	out_hit->obj = NULL;
	i = -1;
	while (++i < scene->element_count)
	{
		if (check_intersection(&scene->elements[i], ray, &t, &uv))
		{
			if (t >= 0 && t < out_hit->t)
			{
				out_hit->t = t;
				out_hit->uv = uv;
				out_hit->obj = &scene->elements[i];
			}
		}
	}
	if (!out_hit->obj)
		return (0);
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
