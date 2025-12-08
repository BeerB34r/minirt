/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/18 16:28:30 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/08 14:03:15 by alkuijte      ########   odam.nl         */
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

#ifndef MINIRT_UTILS_H
# define MINIRT_UTILS_H

# include <stddef.h>
# include <minirt_declarations.h>

char
	**file_to_array(
		const char *file
		);	// FILE: utils/file_to_array.c
void
	free_array(
		char **array
		);	// FILE: utils/free_array.c
/**
 * splits all strings in a given array of strings using ft_split
 *
 * @param str_array array of strings to be split
 * @param depth used in split_str_array's recursion, call with 0
 * @return a malloced array of arrays of strings
 */
char
	***split_str_array(
		char **str_array,
		int depth
		);	// FILE: utils/split_str_array.c
/**
 * helper function to free the return of split_str_array()
 */
void
	free_split_array(
		char ***split_array
		);	// FILE: utils/free_split_array.c
size_t
	count_fields(
		char **element_fields
		);	// FILE: utils/count_fields.c

int	
	get_int(
		const char *str,
		int *store
		);	// FILE: utils/get_int.c
int	
	get_int_limit(
		const char *str,
		int *store,
		int lower_bound,
		int upper_bound
		);	// FILE: utils/get_int_limit.c
/**
 * parses the entirety of a string into a floating point number
 * returns positive on error, supports case-insensitive regex: 
 * "-?([0-9]+(\.[0-9]*)?[fF]?|inf(inity)?)"
 */
int	
	get_real(
		const char *str,
		double *store
		);	// FILE: utils/get_int.c
int	
	get_real_limit(
		const char *str,
		double *store,
		double lower_bound,
		double upper_bound
		);	// FILE: utils/get_int_limit.c
int	
	get_real_int(
		const char *str,
		double *store
		);	// FILE: utils/get_real_int.c
int	
	get_real_int_limit(
		const char *str,
		double *store,
		double lower_bound,
		double upper_bound
		);	// FILE: utils/get_real_int_limit.c
int	
	get_vec3(
		const char *str,
		t_vec3 *store
		);	// FILE: utils/get_vec3.c
int	
	get_vec4(
		const char *str,
		t_vec4 *store
		);	// FILE: utils/get_vec4.c
int	
	get_norm(
		const char *str,
		t_vec3 *store
		);	// FILE: utils/get_norm.c
int	
	get_rgba(
		const char *str,
		struct s_rgba *colour
		);	// FILE: utils/get_rgba.c

#endif // MINIRT_UTILS_H
