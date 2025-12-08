/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/19 21:34:30 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/08 17:46:37 by alkuijte      ########   odam.nl         */
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

static void
	set_triangle_normal(
struct s_rt_element_triangle *tri
)
{
	tri->normal = vec3_cross_product(
			vec3_sub(tri->v2, tri->v1),
			vec3_sub(tri->v3, tri->v1)
			);
	if (!vec3_is_normalised(tri->normal))
		tri->normal = vec3_normalise(tri->normal);
}

int
	parse_triangle(
char **element_fields,
struct s_rt_scene *scene
)
{
	struct s_rt_element_triangle	result;

	if (count_fields(element_fields) != TRIANGLE_FIELDS + 1)
		ft_dprintf(2, ERR E_FIELD, "triangle");
	else if (
		!get_vec3(element_fields[1], &result.v1)
		&& !get_vec3(element_fields[2], &result.v2)
		&& !get_vec3(element_fields[3], &result.v3)
		&& !get_rgba(element_fields[4], &result.colour)
	)
	{
		scene->elements[(scene->element_count)].type = TRIANGLE;
		set_triangle_normal(&result);
		scene->elements[(scene->element_count)].material.colour = result.colour;
		scene->elements[(scene->element_count)].material.ambi_reflectivity = DEFAULT_AMBI_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.diff_reflectivity = DEFAULT_DIFF_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.spec_reflectivity = DEFAULT_SPEC_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.abso_reflectivity = DEFAULT_ABSO_REFLECTIVITY;
		scene->elements[(scene->element_count)].material.shininess = DEFAULT_SHININESS;
		scene->elements[(scene->element_count)].intersect = triangle_int;
		scene->elements[(scene->element_count)].data = &scene->elements[(scene->element_count)].triangle;
		scene->elements[(scene->element_count)++].triangle = result;
		return (0);
	}
	return (1);
}
