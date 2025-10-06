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
#include <libft.h>
#include <minirt_math.h>
#include <math.h>
#include <minirt_declarations.h>
#include <MLX42.h>

#define HEIGHT 200
#define WIDTH 200

int
	check_intersection(
struct s_rt_element object,
struct s_vec3 line_origin,
struct s_vec3 line_vector
)
{
	if (object.type == SUPERQUADRIC)
	{
		double	res;
		res = closest_superquadric_intersection(object, line_origin, line_vector);
		printf("%f\n", res);
		return (!isnan(res));
	}
	return (0);
}

typedef struct s_view_plane
{
	struct s_vec3	origin;
	struct s_vec3	t_norm;
	struct s_vec3	v_norm;
	struct s_vec3	b_norm;
	int				m;	// height
	int				k;	// width
	int				fov;
	double			theta;
	double			g_x;
	double			g_y;
	struct s_vec3	q_x;
	struct s_vec3	q_y;
	struct s_vec3	p_1m;
}	t_fov;

static void
	populate_view_plane(
t_fov *data
)
{
	data->v_norm = (struct s_vec3){
		.x = data->t_norm.y, .y = data->t_norm.z, .z = data->t_norm.x};
	data->b_norm = (struct s_vec3){
		.x = data->t_norm.z, .y = data->t_norm.x, .z = data->t_norm.y};
	data->theta = data->fov * (M_PI / 180);
	data->g_x = tan(data->theta / 2) / 2;
	data->g_y = data->g_x * ((data->m - 1.0) / (data->k / 1.0));
	data->q_x = vec3_scalar_mul(data->b_norm, (2 * data->g_x) / (data->k - 1));
	data->q_y = vec3_scalar_mul(data->v_norm, (2 * data->g_y) / (data->m - 1));
	data->p_1m = vec3_sub(vec3_sub(
				data->t_norm,
				vec3_scalar_mul(data->b_norm, data->g_x)),
			vec3_scalar_mul(data->v_norm, data->g_y));
}

struct s_vec3
	camera_angle(
t_fov fov,
int i,
int j
)
{
	const struct s_vec3	unnormalised = vec3_add(vec3_add(
					fov.p_1m,
					vec3_scalar_mul(fov.q_x, i - 1)),
				vec3_scalar_mul(fov.q_y, j - 1));

	return (vec3_normalise(unnormalised));
}

void
	render_scene(
struct s_rt_scene scene
)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_fov			fov;
	bool			hit;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	mlx = mlx_init(WIDTH, HEIGHT, "she trace on my rays", true);
	if (!mlx)
		return ;
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!img)
	{
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
			while (++k < scene.element_count)
				if (check_intersection(scene.elements[k],
						scene.camera.pos,
						camera_angle(fov, i, j)))
					hit = true;
			if (hit)
				mlx_put_pixel(img, i, j, 0xFFFFFFFF);
			else
				mlx_put_pixel(img, i, j, 0x00000000);
		}
	}
	if (mlx_image_to_window(mlx, img, 0, 0))
	{
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		return ;
	}
	mlx_loop(mlx);
}
