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

#include <libft.h>
#include <minirt_declarations.h>
#include <minirt_mlx.h>
#include <MLX42.h>
#include <unistd.h>

static
void
	progress_bar(
unsigned int enumerator,
unsigned int denominator
)
{
	const char		*empty = "[──────────]";
	unsigned int	i;
	char			bar[32];

	if (enumerator == denominator)
	{
		write(STDOUT_FILENO, "\033[G\033[J[100%]\n", 14);
		return ;
	}
	ft_printf("\033[G\033[J[%3i%%]", (enumerator * 100) / denominator);
	i = -1;
	ft_memcpy(bar, empty, 32);
	while (++i < 10 && ((enumerator * 10) / denominator) > i)
		ft_memcpy(&bar[(i * 3) + 1], "█", 3);
	write(STDOUT_FILENO, bar, 32);
}

void
	paint_pixels(
mlx_image_t *img,
enum e_camera_mode mode,
t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
struct s_rt_scene scene,
int depth
)
{
	const int		max_depth = depth;
	static int		depth_reached = -1;
	unsigned int	x;
	unsigned int	y;
	unsigned int	i;
	unsigned int	j;
	struct s_rgba	value;

	if (depth_reached == -1)
		depth_reached = depth;
	while (depth >= 0)
	{
		x = -1;
		while ((++x * (1 << depth)) < VIEWPORT_WIDTH)
		{
			progress_bar(x * (1 << depth), VIEWPORT_WIDTH);
			y = -1;
			while ((++y * (1 << depth)) < VIEWPORT_HEIGHT)
			{
				get_pixel_value((struct s_get_pixel_params){
					.mode = mode, .scene = scene,
					.x = x * (1 << depth), .y = y * (1 << depth)
				}, angles, &value);
				i = -1;
				while (++i < (1 << depth)
					&& (x * (1 << depth)) + i < VIEWPORT_WIDTH)
				{
					j = -1;
					while (++j < (1 << depth)
						&& (y * (1 << depth)) + j < VIEWPORT_HEIGHT)
					{
						if (max_depth == depth
							|| ((x * (1 << depth)) + i) % (1 << (depth + 1))
							|| ((y * (1 << depth)) + i) % (1 << (depth + 1)))
							mlx_put_pixel(img,
								(x * (1 << depth)) + i, (y * (1 << depth)) + j,
								value.hex);
					}
				}
			}
		}
		progress_bar(VIEWPORT_WIDTH, VIEWPORT_WIDTH);
		depth--;
		if (depth == depth_reached - 1)
		{
			depth_reached--;
			return ;
		}
	}
}

struct params
{
	mlx_image_t *img;
	enum e_camera_mode mode;
	t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT];
	struct s_rt_scene scene;
	int max_depth;
};

void
	testhook(
void* param
)
{
	struct params *const	p = param;
	static int				depth = -2;

	if (depth == -2)
		depth = p->max_depth;

	if (depth > -1)
	{
		ft_printf("[%i/%i]\n", p->max_depth - depth, p->max_depth);
		paint_pixels(p->img, p->mode, p->angles, p->scene, depth);
		depth--;
	}
}

void
	render_scene(
struct s_rt_scene scene
)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				major_axis;
	int				depth;
	/*t_line			angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT];*/
	struct params	p;

	if (get_viewport(&mlx, &img, (t_viewport){
			VIEWPORT_WIDTH, VIEWPORT_HEIGHT, VIEWPORT_TITLE, VIEWPORT_RESIZABLE
		}))
		return ;
	populate_plane_array(scene.camera, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, p.angles);
	/*render_image(img, SURFACE_NORMAL, angles, scene);*/
	major_axis = VIEWPORT_WIDTH;
	depth = 0;
	if (VIEWPORT_HEIGHT > VIEWPORT_WIDTH)
		major_axis = VIEWPORT_HEIGHT;
	while ((1 << depth) < major_axis)
		depth++;
	p.max_depth = depth;
	p.img = img;
	p.mode = SURFACE_NORMAL;
	p.scene = scene;
	mlx_loop_hook(mlx, testhook, &p);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
