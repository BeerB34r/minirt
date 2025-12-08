/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sphere.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/19 21:15:06 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/08 14:04:24 by alkuijte      ########   odam.nl         */
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
#include <minirt_utils.h>
#include <minirt_declarations.h>
#include <minirt_math.h>
#include <minirt_error.h>

int
	parse_sphere(
char **element_fields,
struct s_rt_scene *scene
)
{
	struct s_rt_element_sphere	result;

	if (count_fields(element_fields) != SPHERE_FIELDS + 1)
		ft_dprintf(2, ERR E_FIELD, "sphere");
	else if (
		!get_vec3(element_fields[1], &result.pos)
		&& !get_real(element_fields[2], &result.radius)
		&& !get_rgba(element_fields[3], &result.colour)
	)
	{
		scene->elements[(scene->element_count)].type = SPHERE;
		scene->elements[(scene->element_count)].material.colour = result.colour;
		scene->elements[(scene->element_count)].material.ambi_reflectivity = DEFAULT_AMBI_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.diff_reflectivity = DEFAULT_DIFF_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.spec_reflectivity = DEFAULT_SPEC_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.abso_reflectivity = DEFAULT_ABSO_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.shininess = DEFAULT_SHININESS;
		scene->elements[(scene->element_count)].intersect = sphere_int;
		scene->elements[(scene->element_count)].data = &scene->elements[(scene->element_count)].sphere;

		scene->elements[(scene->element_count)++].sphere = result;
		return (0);
	}
	return (1);
}

