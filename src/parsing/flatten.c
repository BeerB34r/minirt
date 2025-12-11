/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   flatten.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/12/11 22:50:29 by mde-beer            #+#    #+#           */
/*   Updated: 2025/12/11 23:04:57 by mde-beer            ########   odam.nl   */
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
#include <minirt_parse.h>
#include <minirt_utils.h>
#include <minirt_error.h>
#include <unistd.h>
#include <minirt_math.h>

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

static
void
	set_tri_data(
struct s_rt_element_triangle tri,
struct s_rt_element *new_element
)
{
	new_element->triangle = tri;
	new_element->material.colour.hex
		= ((((tri.attr >> 0) & 0b1111) * 8) << 24)
		+ ((((tri.attr >> 4) & 0b1111) * 8) << 16)
		+ ((((tri.attr >> 8) & 0b1111) * 8) << 8)
		+ 0xFF;
	if (new_element->material.colour.hex == 0x000000FF)
		new_element->material.colour.hex = PIXEL_STL_TRI_FALLBACK;
	new_element->material.ambi_reflectivity = DEFAULT_AMBI_REFLECTIVITY;
	new_element->material.diff_reflectivity = DEFAULT_DIFF_REFLECTIVITY;
	new_element->material.spec_reflectivity = DEFAULT_SPEC_REFLECTIVITY;
	new_element->material.abso_reflectivity = DEFAULT_ABSO_REFLECTIVITY;
	new_element->material.shininess = DEFAULT_SHININESS;
	new_element->intersect = triangle_int;
	new_element->data = &new_element->triangle;
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
			set_tri_data(current.triangles[j],
				&new_elements[i + ++offset]);
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
	new_elements = ft_calloc(scene->element_count - stl_count + tri_count + 1,
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

int
	flatten(
int parse_return,
struct s_rt_scene *scene
)
{
	if (parse_return)
		return (parse_return);
	if (flatten_stls(scene))
		return (1);
	if (extract_lights(scene))
		return (1);
	return (0);
}
