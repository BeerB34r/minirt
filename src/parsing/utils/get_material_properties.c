/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_material_properties.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/11 17:25:47 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/12 16:30:58 by alkuijte      ########   odam.nl         */
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

#include <unistd.h>
#include <libft.h>
#include <minirt_utils.h>
#include <minirt_error.h>

static
int
	get_custom_material_properties(
const char *str,
struct s_material *material
)
{
	char **const		split = ft_split(str, ',');
	double				values[5];

	if (!split)
	{
		ft_dprintf(STDERR_FILENO, ERR E_OOM);
		return (1);
	}
	else if (count_fields(split) != 5)
	{
		free_array(split);
		ft_dprintf(STDERR_FILENO, ERR E_FIELD, "material properties");
		return (1);
	}
	else if (get_real_limit(split[0], &values[0], 0, 1)
		|| get_real_limit(split[1], &values[1], 0, 1)
		|| get_real_limit(split[2], &values[2], 0, 1)
		|| get_real_limit(split[3], &values[3], 0, 1)
		|| get_real_limit(split[4], &values[4], 0, 5000)
	)
	{
		free_array(split);
		return (1);
	}
	*material = (struct s_material){
			.colour.hex = 0,
			.spec_reflectivity = values[0],
			.diff_reflectivity = values[1],
			.ambi_reflectivity = values[2],
			.abso_reflectivity = values[3],
			.shininess = values[4],
			.texture = NULL,
			.bump_map = NULL,
	};
	free_array(split);
	return (0);
}

int
	get_material_properties(
const char *str,
struct s_material *material
)
{
	if (!ft_strncmp(str, "DEFAULT", 8))
	{
		*material = (struct s_material){
			.colour.hex = 0,
			.spec_reflectivity = DEFAULT_SPEC_REFLECTIVITY,
			.diff_reflectivity = DEFAULT_DIFF_REFLECTIVITY,
			.ambi_reflectivity = DEFAULT_AMBI_REFLECTIVITY,
			.abso_reflectivity = DEFAULT_ABSO_REFLECTIVITY,
			.shininess = DEFAULT_SHININESS,
			.texture = NULL,
			.bump_map = NULL,
		};
		return (0);
	}
	return (get_custom_material_properties(str, material));
}
