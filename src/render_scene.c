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

struct s_painter
{
	mlx_image_t		*img;
	uint32_t		hexcolor;
	unsigned int	x;
	unsigned int	y;
	int				depth;
	bool			first_call;
};

void
	painter(
struct s_painter p
)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < (1 << p.depth) && (p.x * (1 << p.depth)) + i < VIEWPORT_WIDTH)
	{
		j = -1;
		while (++j < (1 << p.depth)
			&& (p.y * (1 << p.depth)) + j < VIEWPORT_HEIGHT)
		{
			if (p.first_call
				|| ((p.x * (1 << p.depth)) + i) % (1 << (p.depth + 1))
				|| ((p.y * (1 << p.depth)) + i) % (1 << (p.depth + 1)))
				mlx_put_pixel(
					p.img,
					(p.x * (1 << p.depth)) + i,
					(p.y * (1 << p.depth)) + j,
					p.hexcolor
					);
		}
	}
}

struct s_progressive_rendering_params
{
	mlx_image_t			*img;
	enum e_camera_mode	mode;
	t_line				angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT];
	struct s_rt_scene	scene;
	int					max_depth;
};

void
	paint_pixels(
struct s_progressive_rendering_params *p,
int depth
)
{
	unsigned int	x;
	unsigned int	y;
	struct s_rgba	value;

	(void)p;
	x = -1;
	while ((++x * (1 << depth)) < VIEWPORT_WIDTH)
	{
		progress_bar(x * (1 << depth), VIEWPORT_WIDTH);
		y = -1;
		while ((++y * (1 << depth)) < VIEWPORT_HEIGHT)
		{
			get_pixel_value((struct s_get_pixel_params){
				.mode = p->mode, .scene = p->scene,
				.x = x * (1 << depth),
				.y = y * (1 << depth)},
				p->angles,
				&value);
			painter((struct s_painter){.img = p->img, .depth = depth,
				.x = x, .y = y, .hexcolor = value.hex,
				.first_call = p->max_depth == depth});
		}
	}
	progress_bar(VIEWPORT_WIDTH, VIEWPORT_WIDTH);
}

void
	progressive_rendering(
void *param
)
{
	struct s_progressive_rendering_params *const	p = param;
	static bool										done = false;
	static int										depth = -1;

	if (done)
		return ;
	else if (depth < 0)
		depth = p->max_depth;
	else
		write(1, "\033[F\033[F", 7);
	progress_bar(p->max_depth - depth, p->max_depth + 1);
	ft_printf("Block size: %ipx\n", 1 << depth);
	paint_pixels(p, depth);
	if (depth)
		depth--;
	else
	{
		write(1, "\033[F\033[F", 7);
		progress_bar(1, 1);
		done = true;
	}
}

void
	render_scene(
struct s_rt_scene scene
)
{
	mlx_t									*mlx;
	mlx_image_t								*img;
	int										major_axis;
	int										depth;
	struct s_progressive_rendering_params	p;

	major_axis = VIEWPORT_WIDTH;
	if (VIEWPORT_HEIGHT > VIEWPORT_WIDTH)
		major_axis = VIEWPORT_HEIGHT;
	depth = 0;
	while ((1 << depth) < major_axis)
		depth++;
	if (get_viewport(&mlx, &img, (t_viewport){VIEWPORT_WIDTH, VIEWPORT_HEIGHT,
			VIEWPORT_TITLE, VIEWPORT_RESIZABLE}))
		return ;
	p.max_depth = depth;
	p.img = img;
	p.mode = SURFACE_NORMAL;
	p.scene = scene;
	populate_plane_array(
		scene.camera, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, p.angles);
	mlx_loop_hook(mlx, progressive_rendering, &p);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
