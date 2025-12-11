/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/19 21:34:30 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/11 15:32:57 by alkuijte      ########   odam.nl         */
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

static void
	set_triangle_uv(
		t_rt_element_triangle *t
)
{
	double	l_e1;
	double	l_e2;
	double	tmp;

	t->tr_uv.e1 = vec3_sub(t->v2, t->v1);
	t->tr_uv.e2 = vec3_sub(t->v3, t->v1);
	l_e1 = vec3_length(t->tr_uv.e1);
	l_e2 = vec3_length(t->tr_uv.e2);
	t->tr_uv.uv1 = (t_vec2){0.0f, 0.0f};
	t->tr_uv.uv2 = (t_vec2){l_e1, 0.0f};
	t->tr_uv.uv3 = (t_vec2){0.0f, l_e2};
	t->tr_uv.du1 = t->tr_uv.uv2.x - t->v1.x;
	t->tr_uv.dv1 = t->tr_uv.uv2.y - t->tr_uv.uv1.y;
	t->tr_uv.du2 = t->tr_uv.uv3.x - t->tr_uv.uv1.x;
	t->tr_uv.dv2 = t->tr_uv.uv3.y - t->tr_uv.uv1.y;
	tmp = t->tr_uv.du1 * t->tr_uv.dv2 - t->tr_uv.du2 * t->tr_uv.dv1;
	t->tr_uv.r = 1.0f / tmp;
	if (t->tr_uv.r == 0.0f)
		t->tr_uv.r = EPSILON;
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
		set_triangle_uv(&result);
		obj->type = TRIANGLE;
		obj->material = (t_material){.colour = result.colour,
			.ambi_reflectivity = DEFAULT_AMBI_REFLECTIVITY,
			.diff_reflectivity = DEFAULT_DIFF_REFLECTIVITY,
			.spec_reflectivity = DEFAULT_SPEC_REFLECTIVITY,
			.abso_reflectivity = DEFAULT_ABSO_REFLECTIVITY,
			.shininess = DEFAULT_SHININESS,
			.texture = mlx_load_png("./textures/cat.png"),
			.bump_map = mlx_load_png("./textures/bump_map.png")};
		obj->intersect = triangle_int;
		obj->data = &obj->triangle;
		obj->triangle = result;
		scene->element_count += 1;
		return (0);
	}
	return (1);
}
