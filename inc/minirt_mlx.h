/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   minirt_mlx.h                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/10/31 18:06:32 by mde-beer            #+#    #+#           */
/*   Updated: 2025/10/31 20:02:51 by mde-beer            ########   odam.nl   */
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

#ifndef MINIRT_MLX_H
# define MINIRT_MLX_H

# define VIEWPORT_HEIGHT 500
# define VIEWPORT_WIDTH 500
# define VIEWPORT_TITLE "she trace on my rays"
# define VIEWPORT_RESIZABLE 1

# define PIXEL_TRANSPARENT 0x00000000
# define PIXEL_BLACK 0x000000FF
# define PIXEL_WHITE 0xFFFFFFFF
# define PIXEL_RED 0xFF0000FF
# define PIXEL_BLU 0x0000FFFF
# define PIXEL_GRE 0x00FF00FF

# define CAMERA_MODE_COUNT 2

# include <stdbool.h>
# include <minirt_declarations.h>
# include <MLX42.h>

typedef struct s_viewport_metadata
{
	unsigned int	w;
	unsigned int	h;
	char			*title;
	bool			resizable;
}	t_viewport;

enum e_camera_mode
{
	HIT_OR_MISS,
	SURFACE_NORMAL,
};
struct s_camera_mode
{
	enum e_camera_mode	mode;
	void				(*func)(
			mlx_image_t *,
			t_line[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
			struct s_rt_scene,
			unsigned int,
			unsigned int,
			unsigned int,
			double
			);
};

# define HIT_OR_MISS_PIXEL_HIT PIXEL_WHITE
# define HIT_OR_MISS_PIXEL_MISS PIXEL_BLACK

void
	hit_or_miss_color(
		mlx_image_t *img,
		t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
		struct s_rt_scene scene,
		unsigned int obj,
		unsigned int x,
		unsigned int y,
		double t
		);	// FILE: mlx/modes/hit_or_miss.c
void
	surface_normal_color(
		mlx_image_t *img,
		t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
		struct s_rt_scene scene,
		unsigned int obj,
		unsigned int x,
		unsigned int y,
		double t
		);	// FILE: mlx/modes/surface_normal.c

typedef struct s_plane_array_opts
{
	t_vec3			origin;
	t_vec3			p_1m;
	t_vec3			q_x;
	t_vec3			q_y;
	unsigned int	w;
	unsigned int	h;
}	t_plane_array_opts;

void
	populate_plane_array(
		struct s_rt_element_camera c,
		unsigned int w,
		unsigned int h,
		t_line array[VIEWPORT_WIDTH][VIEWPORT_HEIGHT]
		);	// FILE: mlx/view_plane.c

#endif // MINIRT_MLX_H
