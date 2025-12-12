/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_scene.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 14:58:25 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/12 11:29:09 by alkuijte      ########   odam.nl         */
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

#include <minirt_declarations.h>
#include <minirt_mlx.h>
#include <MLX42.h>

void	key_hook(mlx_key_data_t kd, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (kd.key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
		mlx_close_window(mlx);
}

	// struct s_rgba col = scene->elements[0].colour;
	// printf("%d %d %d\n", col.r, col.b, col.g);
	// col = scene->elements[1].colour;
	// printf("%d %d %d\n", col.r, col.b, col.g);
	// col = scene->elements[2].colour;
	// printf("%d %d %d\n", col.r, col.b, col.g);
	// col = scene->elements[3].colour;
	// printf("%d %d %d\n", col.r, col.b, col.g);
	// // col = scene->elements[4].colour;
	// printf("%d %d %d\n", col.r, col.b, col.g);
void	render_scene(struct s_rt_scene *scene)
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
	p = (struct s_progressive_rendering_params){.max_depth = depth,
		.img = img, .mode = DEFAULT, .scene = scene};
	populate_plane_array(scene->camera, VIEWPORT_WIDTH,
		VIEWPORT_HEIGHT, p.angles);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop_hook(mlx, progressive_rendering, &p);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
