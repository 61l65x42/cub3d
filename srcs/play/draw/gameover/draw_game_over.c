/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game_over.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 07:26:13 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 13:51:03 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_screen(t_cubed *cubed)
{
	int			i;
	int			j;
	const int	width = cubed->scene.resol.width;
	const int	height = cubed->scene.resol.height;
	int			*data;

	data = cubed->mlx.img.data;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			data[i * width + j] = 0x000000;
		}
	}
}

int	get_menu_option_color(t_cubed *cubed, int option_index)
{
	if (cubed->selected_option == option_index)
		return (RED);
	return (WHITE);
}

void	draw_game_over_screen(t_cubed *cubed)
{
	const int	center_x = cubed->scene.resol.width / 2;
	const int	center_y = cubed->scene.resol.height / 2;
	const int	image_x = (cubed->scene.resol.width
			- cubed->game_over_texture.width) / 2;
	const int	image_y = (cubed->scene.resol.height
			- cubed->game_over_texture.height) / 2 - 100;

	mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
		cubed->game_over_texture.img.img_ptr, image_x, image_y);
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50, center_y
		+ 50, get_menu_option_color(cubed, 0), "Play Again");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50, center_y
		+ 100, get_menu_option_color(cubed, 1), "Switch Map");
	mlx_string_put(cubed->mlx.mlx_ptr, cubed->mlx.win, center_x - 50, center_y
		+ 150, get_menu_option_color(cubed, 2), "Exit");
}
