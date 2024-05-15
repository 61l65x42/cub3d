/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:39:27 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/15 17:28:12 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare_game(t_cubed *cubed)
{
	// prepare_player(cubed);
	prepare_events(cubed);
	//	prepare_raycaster(cubed);
	//	prepare_textures(cubed);
}

int	render_frames(void *data)
{
	t_cubed	*cubed;

	cubed = data;
	cubed->mlx.img.img_ptr = mlx_new_image(cubed->mlx.mlx_ptr,
			cubed->scene.resolution.width, cubed->scene.resolution.height);
	cubed->mlx.img.data = (int *)mlx_get_data_addr(cubed->mlx.img.img_ptr,
			&cubed->mlx.img.bpp, &cubed->mlx.img.size_l,
			&cubed->mlx.img.endian);
	// update(cubed);
	// draw(cubed);
	mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
		cubed->mlx.img.img_ptr, 0, 0);
	mlx_destroy_image(cubed->mlx.mlx_ptr, cubed->mlx.img.img_ptr);
	return (1);
}

void	start_game(t_cubed *cubed)
{
	t_mlx	*mlx_data;

	mlx_data = &cubed->mlx;
	mlx_data->mlx_ptr = mlx_init();
	if (!cubed->mlx.mlx_ptr)
		ft_clean_exit(cubed, "mlx_init() failed\n");
	// mlx_get_screen_size(mlx->mlx_ptr, &mlx->max_x,
	//&mlx->max_y); maybe in mid game user can change resolution to full ?
	mlx_data->win = mlx_new_window(mlx_data->mlx_ptr,
			cubed->scene.resolution.width, cubed->scene.resolution.height,
			"cub3D");
	if (!mlx_data->win)
		ft_clean_exit(cubed, "mlx_new_window() failed\n");
	prepare_game(cubed);
	mlx_loop_hook(mlx_data->mlx_ptr, render_frames, cubed);
	mlx_loop(mlx_data->mlx_ptr);
}
