/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   clean_split_array.c                                     :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/05/08 04:29:06 by mde-beer            #+#    #+#           */
/*   Updated: 2025/09/18 16:45:28 by mde-beer            ########   odam.nl   */
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
#include <minirt_error.h>
#include <minirt_utils.h>
#include <stdlib.h>
#include <unistd.h>

const static char	*g_required_singletons[][2] = {
{"A", "ambient light"},
{"C", "camera"},
{"L", "light"}
};
#define SINGLETON_IDENTIFIER 0
#define SINGLETON_DESCRIPTION 1
#define REQUIRED_COUNT 3

static int
	is_relevant_line(
char **line
)
{
	if (!ft_strncmp(line[0], "#", 1) || !ft_strncmp(line[0], "\n", 1))
		return (0);
	return (1);
}

static int
	count_relevant_lines(
char ***split_array
)
{
	unsigned int	i;
	unsigned int	count;

	i = -1;
	count = 0;
	while (split_array[++i])
		if (is_relevant_line(split_array[i]))
			count++;
	return (count);
}

static int
	check_singleton(
const char *id,
bool list[REQUIRED_COUNT]
)
{
	size_t	i;

	i = -1;
	while (++i < REQUIRED_COUNT)
		if (!ft_strncmp(g_required_singletons[i][SINGLETON_IDENTIFIER],
			id, ft_strlen(id) + 1))
			break ;
	if (i == REQUIRED_COUNT)
		return (ft_dprintf(STDERR_FILENO, ERR E_UNREC, id));
	if (list[i])
		return (ft_dprintf(STDERR_FILENO, ERR E_DUP,
				g_required_singletons[i][SINGLETON_DESCRIPTION]));
	list[i] = true;
	return (0);
}

static int
	check_required_singletons(
char ***lines
)
{
	bool			list[REQUIRED_COUNT];
	unsigned int	err;
	unsigned int	i;

	i = -1;
	ft_bzero(list, sizeof(list));
	while (lines[++i])
		if (ft_isupper(lines[i][0][0]))
			if (check_singleton(lines[i][0], list))
				return (1);
	i = -1;
	err = 0;
	while (++i < REQUIRED_COUNT)
		if (!list[i])
			err = ft_dprintf(STDERR_FILENO, ERR E_MISS,
					g_required_singletons[i][SINGLETON_DESCRIPTION]);
	return (err);
}

int
	clean_split_array(
char ****split_array
)
{
	size_t			i;
	size_t			j;
	char ***const	og = *split_array;
	const size_t	relevant_lines = count_relevant_lines(og);
	char			***new;

	if (count_fields((char **)og) == relevant_lines)
		return (check_required_singletons(og));
	new = ft_calloc(relevant_lines + 1, sizeof(char **));
	if (!new)
		return (ft_dprintf(STDERR_FILENO, ERR E_OOM));
	i = 0;
	j = 0;
	while (og[i])
	{
		if (!is_relevant_line(og[i]))
			free_array(og[i++]);
		else
			new[j++] = og[i++];
	}
	free(og);
	*split_array = new;
	return (check_required_singletons(*split_array));
}
