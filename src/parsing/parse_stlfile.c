/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_stlfile.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/09/20 12:45:35 by mde-beer            #+#    #+#           */
/*   Updated: 2025/09/20 14:27:38 by mde-beer            ########   odam.nl   */
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
#include <minirt_utils.h>
#include <minirt_error.h>
#include <minirt_declarations.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int
	read_n(
int fd,
void *buf,
size_t n
)
{
	return (read(fd, buf, n) != (ssize_t)n);
}

static int
	get_tri_vec3(
int fd,
struct s_vec3 *store
)
{
	float	float3[3];

	if (read(fd, float3, 12) != 12)
		return (1);
	*store = (struct s_vec3){
		.x = float3[0],
		.y = float3[1],
		.z = float3[2]
	};
	return (0);
}

/**
 * assumes attr is using the Materialise Magics stl dialect
 */
static int
	read_stl_tris(
int fd,
const char *filename,
struct s_rt_element_stlfile *store
)
{
	uint32_t	i;

	i = 0;
	while (i < store->tri_count)
	{
		if (get_tri_vec3(fd, &store->triangles[i].normal)
			|| get_tri_vec3(fd, &store->triangles[i].v1)
			|| get_tri_vec3(fd, &store->triangles[i].v2)
			|| get_tri_vec3(fd, &store->triangles[i].v3)
			|| read_n(fd, &store->triangles[i].attr, 2))
		{
			ft_dprintf(STDERR_FILENO, ERR E_BADR, filename);
			return (1);
		}
		store->triangles[i].color = (struct s_rgba){
			.r = ((store->triangles[i].attr >> 0) & 0b1111) * 8,
			.g = ((store->triangles[i].attr >> 4) & 0b1111) * 8,
			.b = ((store->triangles[i].attr >> 8) & 0b1111) * 8,
			.a = 0
		};
		i++;
	}
	return (read(fd, &i, 1));
}

static int
	read_stl_file(
const char *filename,
struct s_rt_element_stlfile *store
)
{
	const int					fd = open(filename, O_RDONLY);
	struct s_rt_element_stlfile	result;
	int							err;

	if (fd < 0)
		return (ft_dprintf(STDERR_FILENO, ERR E_FD, filename));
	else if (read_n(fd, result.header, 80))
	{
		close(fd);
		return (ft_dprintf(STDERR_FILENO, ERR E_BADR, filename));
	}
	else if (!ft_strncmp((char *)result.header, "solid", 5))
	{
		close(fd);
		return (ft_dprintf(STDERR_FILENO, ERR E_UNSUP));
	}
	else if (read_n(fd, &result.tri_count, 4))
	{
		close(fd);
		return (ft_dprintf(STDERR_FILENO, ERR E_BADR, filename), 1);
	}
	result.triangles = ft_calloc(store->tri_count,
			sizeof(struct s_rt_element_triangle));
	if (!result.triangles)
	{
		close(fd);
		return (ft_dprintf(STDERR_FILENO, ERR E_OOM));
	}
	err = read_stl_tris(fd, filename, &result);
	close(fd);
	if (!err)
		*store = result;
	else
		free(result.triangles);
	return (err);
}

int
	parse_stlfile(
char **element_fields,
struct s_rt_scene *scene
)
{
	struct s_rt_element_stlfile	result;

	if (count_fields(element_fields) != STLFILE_FIELDS + 1)
		ft_dprintf(STDERR_FILENO, ERR E_FIELD, "stlfile");
	else if (!read_stl_file(element_fields[1], &result))
	{
		scene->elements[(scene->element_count)].type = STLFILE;
		scene->elements[(scene->element_count)++].stlfile = result;
		return (0);
	}
	return (1);
}
