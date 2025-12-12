/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   get_viewport.c									 :+:	:+:			*/
/*													 +:+					*/
/*   By: mde-beer <mde-beer@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2025/11/05 20:43:20 by mde-beer	  #+#	#+#				 */
/*   Updated: 2025/12/03 16:45:32 by alkuijte	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇										   */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀										   */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀										   */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀										   */
/*   ——————————————————————————————										   */
/* ************************************************************************** */

#include <MLX42.h>
#include <minirt_mlx.h>
#include <stdio.h>

int	get_viewport(mlx_t **mlx, mlx_image_t **img, t_viewport metadata)
{
	*mlx = mlx_init(metadata.w, metadata.h, metadata.title, metadata.resizable);
	if (!*mlx)
		return (1);
	*img = mlx_new_image(*mlx, (*mlx)->width, (*mlx)->height);
	if (!(*img))
		return (1);
	else if (mlx_image_to_window(*mlx, *img, 0, 0) != -1)
		return (0);
	else
		mlx_delete_image(*mlx, *img);
	mlx_terminate(*mlx);
	*mlx = NULL;
	*img = NULL;
	return (1);
}

// int	get_viewport(mlx_t **mlx, mlx_image_t **img, t_viewport metadata)
// {
// 	*mlx = mlx_init(metadata.w, metadata.h, metadata.title, metadata.resizable);
// 	if (!*mlx)
// 		return (1);
// 	*img = mlx_new_image(*mlx, (*mlx)->width, (*mlx)->height);
// 	if (!(*img))
// 		return (1);
// 	else if (mlx_image_to_window(*mlx, *img, 0, 0) == -1)
// 	{
// 		mlx_delete_image(*mlx, *img);
// 		return (1);
// 	}
// 	mlx_key_hook(*mlx, &key_hook, *mlx);
// 	mlx_loop(*mlx);

// 	mlx_terminate(*mlx);
// 	*mlx = NULL;
// 	*img = NULL;
// 	return (0);
// }
