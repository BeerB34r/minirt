/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/19 21:34:30 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/08 19:20:21 by alkuijte      ########   odam.nl         */
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
	struct s_rt_element				*obj;

	if (count_fields(element_fields) != TRIANGLE_FIELDS + 1)
		ft_dprintf(2, ERR E_FIELD, "triangle");
	else if (!get_vec3(element_fields[1], &result.v1) && !get_vec3(
			element_fields[2], &result.v2) && !get_vec3(element_fields[3],
			&result.v3) && !get_rgba(element_fields[4], &result.colour))
	{
		obj = &scene->elements[(scene->element_count)];
		set_triangle_normal(&result);
		obj->type = TRIANGLE;
		obj->material.colour = result.colour;
		obj->material.ambi_reflectivity = DEFAULT_AMBI_REFLECTIVITY;
		obj->material.diff_reflectivity = DEFAULT_DIFF_REFLECTIVITY;
		obj->material.spec_reflectivity = DEFAULT_SPEC_REFLECTIVITY;
		obj->material.abso_reflectivity = DEFAULT_ABSO_REFLECTIVITY;
		obj->material.shininess = DEFAULT_SHININESS;
		obj->intersect = triangle_int;
		obj->data = &obj->triangle;
		obj->triangle = result;
		scene->element_count += 1;
		return (0);
	}
	return (1);
}
