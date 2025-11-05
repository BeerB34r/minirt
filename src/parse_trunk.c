/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   parse_trunk.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/05/08 08:35:08 by mde-beer            #+#    #+#           */
/*   Updated: 2025/09/19 21:13:30 by mde-beer            ########   odam.nl   */
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
#include <minirt_error.h>
#include <minirt_declarations.h>

const static t_element_id	g_singletons[] = {
{"A", &parse_ambient_light},
{"C", &parse_camera},
{"L", &parse_light},
{NULL, NULL}
};

const static t_element_id	g_primitives[] = {
{"sp", &parse_sphere},
{"pl", &parse_plane},
{"cy", &parse_cylinder},
{"sq", &parse_superquadric},
{"tri", &parse_triangle},
{"stl", &parse_stlfile},
{NULL, NULL}
};

static int
	parse_singleton(
char **element_fields,
struct s_rt_scene *scene
)
{
	size_t	i;

	i = -1;
	while (g_singletons[++i].name)
		if (!ft_strncmp(element_fields[0],
				g_singletons[i].name,
				ft_strlen(g_singletons[i].name) + 1))
			return (g_singletons[i].func(element_fields, scene));
	ft_dprintf(2, ERR E_UNREC, element_fields[0]);
	return (1);
}

static int
	parse_subject(
char **element_fields,
struct s_rt_scene *scene
)
{
	size_t	i;

	i = -1;
	while (g_primitives[++i].name)
		if (!ft_strncmp(element_fields[0],
				g_primitives[i].name,
				ft_strlen(g_primitives[i].name) + 1))
			return (g_primitives[i].func(element_fields, scene));
	ft_dprintf(2, ERR E_UNREC, element_fields[0]);
	return (1);
}

static int
	parse_element(
char **element_fields,
struct s_rt_scene *scene
)
{
	if (ft_isupper(element_fields[0][0]))
		return (parse_singleton(element_fields, scene));
	return (parse_subject(element_fields, scene));
}

static int
	count_elements(
char ***elements
)
{
	int	i;

	i = 0;
	while (elements[i])
		i++;
	return (i);
}

int	
	parse_scene(
struct s_rt_scene *scene,
char ***split_file_array
)
{
	size_t	i;

	ft_bzero(scene, sizeof(struct s_rt_scene));
	if (count_elements(split_file_array) - MANDATORY_SINGLETONS)
		scene->elements = ft_calloc(
				count_elements(split_file_array) - MANDATORY_SINGLETONS,
				sizeof(struct s_rt_element));
	if (!scene->elements
		&& count_elements(split_file_array) - MANDATORY_SINGLETONS)
	{
		ft_dprintf(2, ERR E_OOM);
		return (1);
	}
	i = -1;
	while (split_file_array[++i])
	{
		if (parse_element(split_file_array[i], scene))
		{
			ft_dprintf(2, "parsing failed while processing element %zu: %s\n",
				i + 1, split_file_array[i][0]);
			free_scene(*scene);
			return (1);
		}
	}
	return (0);
}
