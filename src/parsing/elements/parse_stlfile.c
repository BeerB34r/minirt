/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_stlfile.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/20 12:45:35 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/03 19:07:47 by alkuijte      ########   odam.nl         */
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

#include "minirt_math.h"
#include <libft.h>
#include <minirt_utils.h>
#include <minirt_error.h>
#include <minirt_declarations.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int
	get_tri_vec3(
int fd,
t_vec3 *store
)
{
	float	float3[3];

	if (read(fd, float3, 12) != 12)
		return (1);
	*store = (t_vec3){
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
			|| read(fd, &store->triangles[i].attr, 2) != 2)
		{
			ft_dprintf(STDERR_FILENO, ERR E_BADR, filename);
			return (1);
		}
		store->triangles[i].color.hex = 
			((((store->triangles[i].attr >> 0) & 0b1111) * 8) << 24)
			+ ((((store->triangles[i].attr >> 4) & 0b1111) * 8) << 16)
			+ ((((store->triangles[i].attr >> 8) & 0b1111) * 8) << 8)
			+ 0xFF;
		if (store->triangles[i].color.hex == 0x000000FF)
			store->triangles[i].color.hex = PIXEL_STL_TRI_FALLBACK;
		store->triangles[i].normal = vec3_normalise(store->triangles[i].normal);
		i++;
	}
	return (read(fd, &i, 1));
}

static int
	get_file_metadata(
int fd,
const char *filename,
struct s_rt_element_stlfile *store
)
{
	if (fd < 0)
		return (ft_dprintf(STDERR_FILENO, ERR E_FD, filename));
	else if (read(fd, store->header, 80) != 80)
		ft_dprintf(STDERR_FILENO, ERR E_BADR, filename);
	else if (!ft_strncmp((char *)store->header, "solid", 5))
		ft_dprintf(STDERR_FILENO, ERR E_UNSUP);
	else if (read(fd, &store->tri_count, 4) != 4)
		ft_dprintf(STDERR_FILENO, ERR E_BADR, filename);
	else
		return (0);
	close(fd);
	return (1);
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

	if (get_file_metadata(fd, filename, &result))
		return (1);
	result.triangles = ft_calloc(result.tri_count,
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
	char						*trim;

	if (count_fields(element_fields) != STLFILE_FIELDS + 1)
		ft_dprintf(STDERR_FILENO, ERR E_FIELD, "stlfile");
	else
	{
		trim = ft_strchr(element_fields[1], '\n');
		if (trim)
			*trim = 0;
		if (!read_stl_file(element_fields[1], &result))
		{
			scene->elements[(scene->element_count)].type = STLFILE;
			scene->elements[(scene->element_count)++].stlfile = result;
			return (0);
		}
	}
	return (1);
}
