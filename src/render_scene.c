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

#include <stdio.h>
#include <stdbool.h>
#include <libft.h>
#include <minirt_math.h>
#include <math.h>
#include <minirt_declarations.h>
#include <minirt_math_superquadrics.h>
#include <MLX42.h>

#define HEIGHT 500
#define WIDTH 500

double
	sq_int(
t_line lw,
struct s_rt_element_superquadric s
)
{
	if (s.subtype == ELLIPSOID)
		return (sq_e_int(lw, s));
	else if (s.subtype == HYPERBOLOID1)
		return (sq_h1_int(lw, s));
	else if (s.subtype == HYPERBOLOID2)
		return (sq_h2_int(lw, s));
	else if (s.subtype == TOROID)
		return (sq_t_int(lw, s));
	return (NAN);
}

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

typedef struct s_view_plane
{
	t_vec3	origin;
	t_norm	t_norm;
	t_norm	v_norm;
	t_norm	b_norm;
	int		m;	// height
	int		k;	// width
	int		fov;
	double	theta;
	double	g_x;
	double	g_y;
	t_vec3	q_x;
	t_vec3	q_y;
	t_vec3	p_1m;
}	t_fov;

static void
	populate_view_plane(
t_fov *data
)
{
	data->v_norm = (t_norm){
		.x = data->t_norm.y, .y = data->t_norm.z, .z = data->t_norm.x};
	data->b_norm = (t_norm){
		.x = data->t_norm.z, .y = data->t_norm.x, .z = data->t_norm.y};
	data->theta = data->fov * (acos(-1) / 180);
	data->g_x = tan(data->theta / 2) / 2;
	data->g_y = data->g_x * ((data->m - 1.0) / (data->k / 1.0));
	data->q_x = vec3_scalar_mul(data->b_norm, (2 * data->g_x) / (data->k - 1));
	data->q_y = vec3_scalar_mul(data->v_norm, (2 * data->g_y) / (data->m - 1));
	data->p_1m = vec3_sub(vec3_sub(
				data->t_norm,
				vec3_scalar_mul(data->b_norm, data->g_x)),
			vec3_scalar_mul(data->v_norm, data->g_y));
}

t_line
	camera_angle(
t_fov fov,
int i,
int j
)
{
	const t_vec3	unnormalised = vec3_add(vec3_add(
				fov.p_1m,
				vec3_scalar_mul(fov.q_x, i - 1)),
			vec3_scalar_mul(fov.q_y, j - 1));
	const t_line	line = (t_line){
		.normal = vec3_normalise(unnormalised),
		.origin = fov.origin
	};

	return (line);
}

uint32_t
	normal_to_rgba(
t_norm normal
)
{
	uint32_t		internal;

	internal = ((int)trunc(normal.x * 255 * 0.5 + 127) << 24)
		+ ((int)trunc(normal.y * 255 * 0.5 + 127) << 16)
		+ ((int)trunc(normal.z * 255 * 0.5 + 127) << 8)
		+ (255 << 0);
	return (internal);
}

t_norm
	sq_norm(
t_uv uv,
struct s_rt_element_superquadric s
)
{
	if (s.subtype == ELLIPSOID)
		return (sq_e_norm(uv, s));
	else if (s.subtype == HYPERBOLOID1)
		return (sq_h1_norm(uv, s));
	else if (s.subtype == HYPERBOLOID2)
		return (sq_h2_norm(uv, s));
	else if (s.subtype == TOROID)
		return (sq_t_norm(uv, s));
	return ((t_norm){.x = NAN, .y = NAN, .z = NAN});
}

t_uv
	sq_xyz_uv(
t_vec3 pw,
struct s_rt_element_superquadric s
)
{
	if (s.subtype == ELLIPSOID)
		return (sq_e_xyz_uv(pw, s));
	else if (s.subtype == HYPERBOLOID1)
		return (sq_h1_xyz_uv(pw, s));
	else if (s.subtype == HYPERBOLOID2)
		return (sq_h2_xyz_uv(pw, s));
	else if (s.subtype == TOROID)
		return (sq_t_xyz_uv(pw, s));
	return ((t_uv){.u = NAN, .v = NAN});
}

void
	render_scene(
struct s_rt_scene scene
)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_fov			fov;
	double			t;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	mlx = mlx_init(WIDTH, HEIGHT, "she trace on my rays", 1);
	if (!mlx)
		return ;
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!img)
	{
		mlx_terminate(mlx);
		return ;
	}
	if (mlx_image_to_window(mlx, img, 0, 0))
	{
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		return ;
	}
	fov = (t_fov){
		.fov = scene.camera.fov,
		.t_norm = scene.camera.orientation,
		.origin = scene.camera.pos,
		.m = HEIGHT,
		.k = WIDTH
	};
	populate_view_plane(&fov);
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			k = -1;
			t = FP_INFINITE;
			while (++k < scene.element_count)
				if (check_intersection(scene.elements[k],
						camera_angle(fov, i, j), &t))
					break ;
			if (t != FP_INFINITE)
			{
				mlx_put_pixel(img, i, j, normal_to_rgba(
						sq_norm(
							sq_xyz_uv(
								l_t(
									camera_angle(fov, i, j), t),
								scene.elements[k].superquadric),
							scene.elements[k].superquadric)
						)
					);
			}
			else if (t != FP_INFINITE)
				mlx_put_pixel(img, i, j, 0xFFFFFFFF);
			else
				mlx_put_pixel(img, i, j, 0x00000000);
		}
	}
	mlx_loop(mlx);
}
