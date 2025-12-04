/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_superquadric.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/19 21:25:50 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/04 14:59:42 by alkuijte      ########   odam.nl         */
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

#include <float.h>
#include <libft.h>
#include <math.h>
#include <minirt_utils.h>
#include <minirt_declarations.h>
#include <minirt_math_superquadrics.h>
#include <minirt_error.h>

// e h1 h2 t
const static struct s_sq_subtype
{
	char				*s;
	enum e_sq_subtype	t;
}	g_sq_subtypes[] = {
	{"e", ELLIPSOID},
	{"h1", HYPERBOLOID1},
	{"h2", HYPERBOLOID2},
	{"t", TOROID}
};
#define SQ_SUBTYPES 4

static int
	get_sq_subtype(
const char *str,
enum e_sq_subtype *store
)
{
	unsigned int	i;

	i = -1;
	while (++i < SQ_SUBTYPES)
	{
		if (ft_strncmp(
				str,
				g_sq_subtypes[i].s,
				ft_strlen(g_sq_subtypes[i].s) + 1)
		)
			continue ;
		*store = g_sq_subtypes[i].t;
		return (0);
	}
	return (1);
}

static int
	final_touches(
struct s_rt_element_superquadric result,
struct s_rt_scene *scene
)
{
	result.e1 = result.e1p / result.e1q;
	result.e2 = result.e2p / result.e2q;
	result.a4 = result.a / sqrt(pow(result.a1, 2) + pow(result.a2, 2));
	scene->elements[(scene->element_count)].type = SUPERQUADRIC;
	scene->elements[(scene->element_count)].material.colour = result.color;
	scene->elements[(scene->element_count)].material.reflectivity = DEFAULT_REFLECTIVITY;
	scene->elements[(scene->element_count)].material.ior = DEFAULT_IOR;
	scene->elements[(scene->element_count)].intersect = sq_int;
	scene->elements[(scene->element_count)].data = &scene->elements[(scene->element_count)].superquadric;
	scene->elements[(scene->element_count)++].superquadric = result;
	return (0);
}

int
	parse_superquadric(
char **element_fields,
struct s_rt_scene *scene
)
{
	struct s_rt_element_superquadric	result;

	if (count_fields(element_fields) != SUPERQUADRIC_FIELDS + 1)
		ft_dprintf(2, ERR E_FIELD, "superquadric");
	else if (
		!get_sq_subtype(element_fields[1], &result.subtype)
		&& !get_vec3(element_fields[2], &result.pos)
		&& !get_vec4(element_fields[3], &result.rot)
		&& !get_real_int_limit(element_fields[4], &result.e1p, 1, NAN)
		&& !get_real_int_limit(element_fields[5], &result.e1q, 1, NAN)
		&& !get_real_int_limit(element_fields[6], &result.e2p, 1, NAN)
		&& !get_real_int_limit(element_fields[7], &result.e2q, 1, NAN)
		&& !get_real_limit(element_fields[8], &result.a1, nextafter(0, 1), NAN)
		&& !get_real_limit(element_fields[9], &result.a2, nextafter(0, 1), NAN)
		&& !get_real_limit(element_fields[10], &result.a3, nextafter(0, 1), NAN)
		&& !get_real_limit(element_fields[11], &result.a, nextafter(0, 1), NAN)
		&& !get_rgba(element_fields[12], &result.color)
	)
		return (final_touches(result, scene));
	return (1);
}
