/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt_parse.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 19:07:54 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/11 16:30:38 by alkuijte      ########   odam.nl         */
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

#include <libft.h>
#include <minirt_parse.h>
#include <minirt_utils.h>
#include <minirt_error.h>
#include <unistd.h>
#include <minirt_math.h>
#include <stdio.h>

static unsigned int
	count_element_type(
enum e_element_type type,
struct s_rt_element *elements,
unsigned int element_count
)
{
	unsigned int	type_count;
	unsigned int	i;

	i = -1;
	type_count = 0;
	while (++i < element_count)
		if (elements[i].type == type)
			type_count++;
	return (type_count);
}

static int
	extract_lights(
struct s_rt_scene *scene
)
{
	unsigned int	i;
	unsigned int	j;

	scene->light_count = count_element_type(
			LIGHT, scene->elements, scene->element_count);
	if (!scene->light_count)
		return (0);
	scene->lights = ft_calloc(scene->light_count,
			sizeof(struct s_rt_element_light));
	if (!scene->lights)
	{
		ft_dprintf(STDERR_FILENO, ERR E_OOM);
		return (1);
	}
	i = -1;
	j = 0;
	while (++i < scene->element_count)
		if (scene->elements[i].type == LIGHT)
			scene->lights[j++] = scene->elements[i].light;
	return (0);
}

static void
	intersperse_tris(
struct s_rt_element *new_elements,
struct s_rt_element *old_elements,
unsigned int old_element_count)
{
	struct s_rt_element_stlfile	current;
	unsigned int				i;
	unsigned int				j;
	unsigned int				offset;

	i = -1;
	offset = 0;
	while (++i < old_element_count)
	{
		if (old_elements[i].type != STLFILE)
		{
			new_elements[i + offset] = old_elements[i];
			continue ;
		}
		current = old_elements[i].stlfile;
		j = -1;
		while (++j < current.tri_count)
		{
			new_elements[i + ++offset].triangle = current.triangles[j];
			new_elements[i + offset].material.colour.hex = 
				((((current.triangles[j].attr >> 0) & 0b1111) * 8) << 24)
				+ ((((current.triangles[j].attr >> 4) & 0b1111) * 8) << 16)
				+ ((((current.triangles[j].attr >> 8) & 0b1111) * 8) << 8)
				+ 0xFF;
			if (new_elements[i + offset].material.colour.hex == 0x000000FF)
				new_elements[i + offset].material.colour.hex = PIXEL_STL_TRI_FALLBACK;
			// new_elements[i + offset].material.ambi_reflectivity = DEFAULT_AMBI_REFLECTIVITY;
			// new_elements[i + offset].material.diff_reflectivity = DEFAULT_DIFF_REFLECTIVITY;
			// new_elements[i + offset].material.spec_reflectivity = DEFAULT_SPEC_REFLECTIVITY;
			// new_elements[i + offset].material.abso_reflectivity = DEFAULT_ABSO_REFLECTIVITY;
			// new_elements[i + offset].material.shininess = DEFAULT_SHININESS;
			// new_elements[i + offset].intersect = triangle_int;
			new_elements[i + offset].data = &new_elements[i + offset].triangle;
		}
	}
}

static int
	flatten_stls(
struct s_rt_scene *scene
)
{
	const unsigned int	stl_count = count_element_type(
			STLFILE, scene->elements, scene->element_count);
	struct s_rt_element	*new_elements;
	unsigned int		tri_count;
	unsigned int		i;

	if (!stl_count)
		return (0);
	i = -1;
	tri_count = 0;
	while (++i < scene->element_count)
		if (scene->elements[i].type == STLFILE)
			tri_count += scene->elements[i].stlfile.tri_count;
	new_elements = ft_calloc(scene->element_count - stl_count + tri_count,
			sizeof(struct s_rt_element));
	if (!new_elements)
	{
		ft_dprintf(STDERR_FILENO, ERR E_OOM);
		return (1);
	}
	intersperse_tris(new_elements, scene->elements, scene->element_count);
	free_scene(*scene);
	scene->elements = new_elements;
	scene->element_count += tri_count - stl_count;
	return (0);
}

static int
	flatten(
int parse_return,
struct s_rt_scene *scene
)
{
	if (parse_return)
		return (parse_return);
	if (extract_lights(scene))
		return (1);
	if (flatten_stls(scene))
		return (1);
	return (0);
}

int	minirt_parse(int ac, char **av, struct s_rt_scene *scene)
{
	char				**file_array;
	char				***split_file;
	int					rval;

	if (ac != 2)
		return (ft_dprintf(2, USAGE, av[0]), 1);
	if (ft_strlen(av[1]) < 4
		|| ft_strncmp(&av[1][ft_strlen(av[1]) - 3], ".rt", 4))
		return (ft_dprintf(2, ERR E_EXT USAGE, av[0]), 1);
	file_array = file_to_array(av[1]);
	if (!file_array)
		return (2);
	split_file = split_str_array(file_array, 0);
	free_array(file_array);
	if (!split_file)
		return (ft_dprintf(2, ERR E_OOM), 3);
	if (clean_split_array(&split_file))
	{
		free_split_array(split_file);
		return (4);
	}
	rval = flatten(parse_scene(scene, split_file), scene);
	free_split_array(split_file);
	return (5 * rval);
}
