/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   render_scene.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/10/06 14:58:25 by mde-beer            #+#    #+#           */
/*   Updated: 2025/10/06 14:58:45 by mde-beer            ########   odam.nl   */
/*                                                                            */
/*   —————No norm compliance?——————                                           */
/*   ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                                           */
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

#include <stdbool.h>
#include <libft.h>
#include <minirt_math.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math_superquadrics.h>
#include <minirt_mlx.h>
#include <MLX42.h>
#include <stdio.h>

int
	check_intersection(
struct s_rt_element object,
t_line line,
double *t
)
{
	double			res;

	if (object.type == SUPERQUADRIC)
	{
		res = sq_int(line, object.superquadric);
		if (res == res)
			*t = res;
		return (res == res);
	}
	return (0);
}

int
	get_viewport(
mlx_t **mlx,
mlx_image_t **img,
t_viewport metadata
)
{
	*mlx = mlx_init(
			metadata.w,
			metadata.h,
			metadata.title,
			metadata.resizable
			);
	if (!*mlx)
		return (1);
	*img = mlx_new_image(
			*mlx,
			(*mlx)->width,
			(*mlx)->height
			);
	if (!(*img))
		;
	else if (mlx_image_to_window(*mlx, *img, 0, 0) != -1)
		return (0);
	else
		mlx_delete_image(*mlx, *img);
	mlx_terminate(*mlx);
	*mlx = NULL;
	*img = NULL;
	return (1);
}

const static
	struct s_camera_mode g_modes[] = {
{HIT_OR_MISS, hit_or_miss_color},
{SURFACE_NORMAL, surface_normal_color}
};

void
	set_pixel_value(
enum e_camera_mode mode,
mlx_image_t *img,
t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
struct s_rt_scene scene,
unsigned int x,
unsigned int y
)
{
	unsigned int	obj;
	unsigned int	i;
	double			t;

	obj = -1;
	t = NAN;
	while (++obj < scene.element_count)
		if (check_intersection(scene.elements[obj], angles[x][y], &t))
			break ;
	i = -1;
	while (++i < CAMERA_MODE_COUNT)
	{
		if (mode == g_modes[i].mode)
		{
			g_modes[i].func(img, angles, scene, obj, x, y, t);
			return ;
		}
	}
}

void
	render_scene(
struct s_rt_scene scene
)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_line			angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT];
	unsigned int	i;
	unsigned int	j;

	if (get_viewport(&mlx, &img, (t_viewport){
			VIEWPORT_WIDTH,
			VIEWPORT_HEIGHT,
			VIEWPORT_TITLE,
			VIEWPORT_RESIZABLE
		}))
		return ;
	populate_plane_array(scene.camera, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, angles);
	i = -1;
	while (++i < VIEWPORT_WIDTH)
	{
		j = -1;
		while (++j < VIEWPORT_HEIGHT)
			set_pixel_value(SURFACE_NORMAL, img, angles, scene, i, j);
	}
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
