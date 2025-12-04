/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_scene.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 14:58:25 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/04 15:48:55 by alkuijte      ########   odam.nl         */
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
#include <stdio.h>

static bool	mlx_hooks(mlx_t	*mlx, struct s_progressive_rendering_params *progressive_rendering_args) {
	if (mlx_loop_hook(mlx, &progressive_rendering, progressive_rendering_args)) {
		return (true);
	}
	return (false);
}

void	render_scene(struct s_rt_scene *scene) {
	mlx_t									*mlx;
	mlx_image_t								*img;
	int										major_axis;
	int										depth;
	struct s_progressive_rendering_params	p;

	major_axis = VIEWPORT_WIDTH;				// Determine major axis
	if (VIEWPORT_HEIGHT > VIEWPORT_WIDTH) {
		major_axis = VIEWPORT_HEIGHT;
	}
	depth = 0;
	while ((1 << depth) < major_axis) {
		depth++;
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
	if (get_viewport(&mlx, &img, (t_viewport){VIEWPORT_WIDTH, VIEWPORT_HEIGHT,
			VIEWPORT_TITLE, VIEWPORT_RESIZABLE})) {
		return ;
	}
	p.max_depth = depth;
	p.img = img;
//	p.mode = HIT_OR_MISS;
//	p.mode = SURFACE_NORMAL;
	 p.mode = DEFAULT;
	p.scene = scene;
	populate_plane_array(scene->camera, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, p.angles);
	if (mlx_hooks(mlx, &p)) {
		mlx_loop(mlx);
	}
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
