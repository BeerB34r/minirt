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
int depth
)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	i;
	unsigned int	j;
	uint32_t		value;

	while (depth >= 0)
	{
		while (x)
		{
			while (y)
			{
				i = -1;
				while (++i < (1 << depth) && (x * (1 << depth)) + i < VIEWPORT_WIDTH)
				{
					j = -1;
					while (++j < (1 << depth) && (y * (1 << depth)) + j < VIEWPORT_HEIGHT)
					{
					}
				}
			}
		}
	}
}

static
void
	render_image(
mlx_image_t *img,
enum e_camera_mode mode,
t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
struct s_rt_scene scene
)
{
	unsigned int	major_axis;
	unsigned int	x;
	unsigned int	y;
	unsigned int	depth;

	major_axis = VIEWPORT_WIDTH;
	depth = 0;
	if (VIEWPORT_HEIGHT > VIEWPORT_WIDTH)
		major_axis = VIEWPORT_HEIGHT;
	while ((1 << depth) < major_axis)
		depth++;
	ft_printf("depth required for incremental passes: %i (initial chunk: %i)\n",
		depth, 1 << depth);
	x = -1;
	write(STDOUT_FILENO, "Rendering scene...\n", 20);
	while (++x < VIEWPORT_WIDTH)
	{
		progress_bar(x, VIEWPORT_WIDTH);
		y = -1;
		while (++y < VIEWPORT_HEIGHT)
			set_pixel_value((struct s_set_pixel_params){
				.mode = mode, .img = img,
				.scene = scene, .x = x, .y = y}, angles);
	}
	progress_bar(x, VIEWPORT_WIDTH);
}

void
	render_scene(
struct s_rt_scene scene
)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_line			angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT];

	if (get_viewport(&mlx, &img, (t_viewport){
			VIEWPORT_WIDTH, VIEWPORT_HEIGHT, VIEWPORT_TITLE, VIEWPORT_RESIZABLE
		}))
		return ;
	populate_plane_array(scene.camera, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, angles);
	render_image(img, SURFACE_NORMAL, angles, scene);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
