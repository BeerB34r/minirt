/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt_mlx.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/31 18:06:32 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/10 15:30:31 by alkuijte      ########   odam.nl         */
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

#ifndef MINIRT_MLX_H
# define MINIRT_MLX_H

# ifndef VIEWPORT_HEIGHT
#  define VIEWPORT_HEIGHT 1000
# endif // VIEWPORT_HEIGHT
# ifndef VIEWPORT_WIDTH
#  define VIEWPORT_WIDTH 1000
# endif // VIEWPORT_WIDTH
# ifndef VIEWPORT_TITLE
#  define VIEWPORT_TITLE "miniRT"
# endif // VIEWPORT_TITLE
# ifndef VIEWPORT_RESIZABLE
#  define VIEWPORT_RESIZABLE 0
# endif // VIEWPORT_RESIZABLE

# define PIXEL_TRANSPARENT 0x00000000
# define PIXEL_BLACK 0x000000FF
# define PIXEL_WHITE 0xFFFFFFFF
# define PIXEL_RED 0xFF0000FF
# define PIXEL_BLU 0x0000FFFF
# define PIXEL_GRE 0x00FF00FF
//#define PIXEL_BG 0xFFB3E632
# define PIXEL_BG 0x000000FF

# define CAMERA_MODE_COUNT 2

# include <MLX42.h>
# include <minirt_declarations.h>
# include <stdbool.h>

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
	DEFAULT
};

struct s_mode_func_params
{
	mlx_image_t			*img;
	struct s_rt_scene	*scene;
	struct s_hit		hit;
	unsigned int		x;
	unsigned int		y;
	double				t;
};

struct s_camera_mode
{
	enum e_camera_mode	mode;
	void				(*func)(struct s_mode_func_params p,
			t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
			struct s_rgba * colour);
};

typedef struct s_plane_array_opts
{
	t_vec3			origin;
	t_vec3			p_1m;
	t_vec3			q_x;
	t_vec3			q_y;
	unsigned int	w;
	unsigned int	h;
}	t_plane_array_opts;

struct s_get_pixel_params
{
	enum e_camera_mode	mode;
	struct s_rt_scene	*scene;
	unsigned int		x;
	unsigned int		y;
};

struct s_painter
{
	mlx_image_t		*img;
	uint32_t		hexcolour;
	unsigned int	x;
	unsigned int	y;
	int				depth;
	bool			first_call;
};

struct s_progressive_rendering_params
{
	mlx_image_t			*img;
	enum e_camera_mode	mode;
	t_line				angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT];
	struct s_rt_scene	*scene;
	int					max_depth;
	bool				reset;
};

# define HIT_OR_MISS_PIXEL_HIT PIXEL_WHITE
# define HIT_OR_MISS_PIXEL_MISS PIXEL_BLACK

void	
	hit_or_miss_colour(
		struct s_mode_func_params p,
		t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
		struct s_rgba *colour
		); // FILE: mlx/modes/hit_or_miss.c
void	
	surface_normal_colour(
		struct s_mode_func_params p,
		t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
		struct s_rgba *colour
		); // FILE: mlx/modes/surface_normal.c

void	
	populate_plane_array(
		struct s_rt_element_camera c,
		unsigned int w,
		unsigned int h,
		t_line array[VIEWPORT_WIDTH][VIEWPORT_HEIGHT]
		); // FILE: mlx/view_plane.c
void	
	get_pixel_value(
		struct s_get_pixel_params p,
		t_line (*angles)[VIEWPORT_HEIGHT],
		struct s_rgba *out
		);
int		
	get_viewport(
		mlx_t **mlx,
		mlx_image_t **img,
		t_viewport metadata
		); // FILE: mlx/get_viewport.c
void	
	progressive_rendering(
		void *param
		); // FILE: mlx/progressive_rendering.c
t_vec3	
	get_normal(
		struct s_rt_element obj,
		t_vec3 point
		);
void	
	default_colour(
		struct s_mode_func_params p,
		t_line angles[VIEWPORT_WIDTH][VIEWPORT_HEIGHT],
		struct s_rgba *colour
		);
int		
	find_closest_intersection(
		t_scene *scene,
		t_line ray,
		t_hit *final_hit
		);
t_vec4	
	compute_ambient(
		struct s_rt_element_ambient_light ambient,
		float mat_ambi_refl,
		t_vec4 mat_col
		);
void	
	clamp_colour(
		t_vec4 *colour
		);
uint32_t
	vec4_to_hex(
		t_vec4 c
		);
t_vec4	
	hex_to_vec4(
		uint32_t hex
		);
t_vec4	
	shade(
		struct s_rt_scene *scene,
		t_hit *hit
		);
t_vec4	
	blend_colour(
		t_vec4 a,
		t_vec4 b,
		double r
		);
t_vec4	
	get_light_col(
		struct s_rt_element_light light
		);
t_vec4	
	compute_diffuse(
		t_vec4 light_col,
		t_shade_input in
		);
t_vec4	
	compute_specular(
		t_vec4 light_col,
		t_shade_input in
		);
void	
	get_sphere_uv(
		t_uv	*uv,
		t_vec3	p
		);
t_vec4	
	get_texture_pixel_value(
		mlx_texture_t *texture,
		t_hit *hit
		);
void	
	get_plane_uv(
		t_uv *uv,
		t_vec3 p,
		t_vec3 normal
		);
#endif // MINIRT_MLX_H
