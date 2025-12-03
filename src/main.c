/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/18 16:07:32 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/03 15:33:14 by alkuijte      ########   odam.nl         */
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

#include <errno.h>
#include <libft.h>
#include <minirt_mlx.h>
#include <minirt_error.h>
#include <minirt_declarations.h>
#include <minirt_parse.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <debug.h>

void	render_scene(struct s_rt_scene *scene);

static int	ensure_stack_limit(void) {
	struct rlimit	rl;
	int				rv;

	if (VIEWPORT_HEIGHT < 512 && VIEWPORT_WIDTH < 512)
		return (0);
	rv = getrlimit(RLIMIT_STACK, &rl);
	if (rv) {
		ft_dprintf(STDERR_FILENO, ERR E_STRERR, strerror(errno));
		return (rv);
	}
	if (rl.rlim_cur < (RLIM_INFINITY))
	{
		rl.rlim_cur = RLIM_INFINITY;
		rv = setrlimit(RLIMIT_STACK, &rl);
		if (rv) {
			ft_dprintf(STDERR_FILENO, ERR E_STRERR, strerror(errno));
			return (rv);
		}
	}
	return (0);
}

/**
 * entrypoint to the program
 *
 * @param ac commandline argument count
 * @param av commandline arguments
 */
int	main(int ac, char **av) {
	const int			stack_rval = ensure_stack_limit();
	struct s_rt_scene	scene;
	const int			parse_rval = minirt_parse(ac, av, &scene);
	debug_fp = fopen("debug.txt", "a");
	if (debug_fp == NULL) {
		perror("Failed to open file\n");
		return 1;
	}
	setvbuf(debug_fp, NULL, _IONBF, 0);
	if (stack_rval)
		return (stack_rval);
	if (!parse_rval) {
		render_scene(&scene);
		free_scene(scene);
	}
	fflush(debug_fp);
	fclose(debug_fp);
	return (parse_rval);
}
