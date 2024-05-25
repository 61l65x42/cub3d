/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:39:27 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 06:14:08 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	prepare_game(t_cubed *cubed)
{
	prepare_player(cubed);
	prepare_sprites(cubed);
	prepare_events(cubed);
	prepare_textures(cubed);
	prepare_rays(cubed);
}

static void	update_data(t_cubed *cubed)
{
	update_player_position(&cubed->player, &cubed->scene.map);
	update_player_orientation(&cubed->player);
	update_rays(cubed);
	update_sprite_render_info(cubed);
}

static void	draw_image(t_cubed *cubed)
{
	draw_ceiling(cubed);
	draw_floor(cubed);
	draw_walls(cubed);
	draw_sprites(cubed);
	draw_gun_shooting(cubed);
}

static int	render_frames(void *data)
{
	t_cubed	*cubed;

	cubed = data;
	update_data(cubed);
	draw_image(cubed);
	mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
		cubed->mlx.img.img_ptr, 0, 0);
	if (cubed->game_state == GAME_STATE_MENU)
		draw_menu(cubed);
	return (1);
}

void	start_game(t_cubed *cubed)
{
	t_mlx	*mlx_data;

	mlx_data = &cubed->mlx;
	mlx_data->mlx_ptr = mlx_init();
	if (!cubed->mlx.mlx_ptr)
		ft_clean_exit(cubed, "mlx_init() failed\n");
	mlx_data->win = mlx_new_window(mlx_data->mlx_ptr, cubed->scene.resol.width,
			cubed->scene.resol.height, "cub3D");
	if (!mlx_data->win)
		ft_clean_exit(cubed, "mlx_new_window() failed\n");
	prepare_game(cubed);
	cubed->mlx.img.img_ptr = mlx_new_image(cubed->mlx.mlx_ptr,
			cubed->scene.resol.width, cubed->scene.resol.height);
	cubed->mlx.img.data = (int *)mlx_get_data_addr(cubed->mlx.img.img_ptr,
			&cubed->mlx.img.bpp, &cubed->mlx.img.size_l,
			&cubed->mlx.img.endian);
	mlx_loop_hook(mlx_data->mlx_ptr, render_frames, cubed);
	mlx_loop(mlx_data->mlx_ptr);
}
