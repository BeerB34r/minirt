/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pixel_value.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/05 19:11:13 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/03 16:44:53 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                                           */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                                           */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀                                           */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ——————————————————————————————                                           */
/* ************************************************************************** */

#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <stdio.h>
#include <debug.h>

static int	check_intersection(const struct s_rt_element *object,
			t_line line, double *t)
{
	double	result;

	result = NAN;
	switch (object->type)
	{
		case SUPERQUADRIC:
			result = sq_int(line, object->superquadric);
			break;
		case SPHERE:
			result = sphere_int(line, object->sphere);
			break;
		case PLANE:
			result = plane_int(line, object->plane);
			break;
		case TRIANGLE:
			result = triangle_int(line, object->triangle);
			break;
		case CYLINDER:
			result = cylinder_int(line, object->cylinder);
			break;
		default:
			break;
	}
	if (result == result)
	{
		*t = result;
		return (1);
	}
	return (0);
}

static const struct s_camera_mode	g_modes[] = {
{HIT_OR_MISS, hit_or_miss_color},
{SURFACE_NORMAL, surface_normal_color},
{DEFAULT, default_color}
};

int	find_closest_intersection(t_scene *scene, t_line ray,
			unsigned int *out_obj, double *out_t)
{
	double			t_min;
	int				hit_obj;
	unsigned int	i;
	double			t;

	t_min = INFINITY;
	hit_obj = -1;
	i = -1;
	while (++i < scene->element_count)
	{
		t = NAN;
		if (check_intersection(&scene->elements[i], ray, &t))
		{
			if (t >= 0 && t < t_min)
			{
				t_min = t;
				hit_obj = (int)i;
			}
		}
	}
	if (hit_obj == -1)
		return (0);
	*out_obj = (unsigned int)hit_obj;
	*out_t = t_min;
	return (1);
}

void	get_pixel_value(struct s_get_pixel_params p,
			t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
			struct s_rgba *out)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	closest_obj;
	double			t_min;

	x = p.x;
	y = p.y;
	if (!find_closest_intersection(p.scene, angles[x][y],
		&closest_obj, &t_min))
	{
		out->hex = PIXEL_BG;
		return ;
	}
	g_modes[p.mode].func((struct s_mode_func_params){
		.scene = p.scene,
		.obj = closest_obj,
		.x = x,
		.y = y,
		.t = t_min
	}, angles, out);
}
