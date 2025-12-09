/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   progressive_rendering.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-beer <mde-beer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/07 21:03:33 by mde-beer      #+#    #+#                 */
/*   Updated: 2025/12/09 11:01:12 by alkuijte      ########   odam.nl         */
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
#include <unistd.h>
#include <minirt_declarations.h>
#include <minirt_mlx.h>
#include <stdio.h>

static
void
	progress_bar(
unsigned int enumerator,
unsigned int denominator
)
{
	const char		*empty = "[──────────]";
	unsigned int	i;
	char			bar[32];

	if (enumerator == denominator)
	{
		write(STDOUT_FILENO, "\033[G\033[J[100%]\n", 14);
		return ;
	}
	ft_printf("\033[G\033[J[%3i%%]", (enumerator * 100) / denominator);
	i = -1;
	ft_memcpy(bar, empty, 32);
	while (++i < 10 && ((enumerator * 10) / denominator) > i)
		ft_memcpy(&bar[(i * 3) + 1], "█", 3);
	write(STDOUT_FILENO, bar, 32);
}

static
void
	painter(
struct s_painter p
)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < (1 << p.depth) && (p.x * (1 << p.depth)) + i < VIEWPORT_WIDTH)
	{
		j = -1;
		while (++j < (1 << p.depth)
			&& (p.y * (1 << p.depth)) + j < VIEWPORT_HEIGHT)
		{
			if (p.first_call
				|| ((p.x * (1 << p.depth)) + i) % (1 << (p.depth + 1))
				|| ((p.y * (1 << p.depth)) + i) % (1 << (p.depth + 1)))
				mlx_put_pixel(
					p.img,
					(p.x * (1 << p.depth)) + i,
					(p.y * (1 << p.depth)) + j,
					p.hexcolour
					);
		}
	}
}

static
void
	painters_blueprint(
struct s_progressive_rendering_params *p,
int depth
)
{
	unsigned int	x;
	unsigned int	y;
	struct s_rgba	value;

	(void)p;
	x = -1;
	while ((++x * (1 << depth)) < VIEWPORT_WIDTH)
	{
		progress_bar(x * (1 << depth), VIEWPORT_WIDTH);
		y = -1;
		while ((++y * (1 << depth)) < VIEWPORT_HEIGHT)
		{
			get_pixel_value((struct s_get_pixel_params){
				.mode = p->mode, .scene = p->scene,
				.x = x * (1 << depth),
				.y = y * (1 << depth)},
				p->angles,
				&value);
			painter((struct s_painter){.img = p->img, .depth = depth,
				.x = x, .y = y, .hexcolour = value.hex,
				.first_call = p->max_depth == depth});
		}
	}
	progress_bar(VIEWPORT_WIDTH, VIEWPORT_WIDTH);
}

void	progressive_rendering(void *param)
{
	struct s_progressive_rendering_params *const	p = param;
	static bool										done = false;
	static int										depth = -1;

	if (p->reset)
	{
		done = false;
		depth = -1;
		p->reset = false;
	}
	if (done)
		return ;
	else if (depth < 0)
		depth = p->max_depth;
	else
		write(1, "\033[F\033[F", 7);
	progress_bar(p->max_depth - depth, p->max_depth + 1);
	ft_printf("Block size: %ipx\n", 1 << depth);
	painters_blueprint(p, depth);
	if (depth--)
		return ;
	write(1, "\033[F\033[F", 7);
	progress_bar(1, 1);
	done = true;
}
