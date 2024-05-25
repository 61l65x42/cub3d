/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 07:30:08 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_vertical_sprite_line(t_cubed *cubed, int stripe,
		t_sprite_render_info *info, t_texture *texture)
{
	int			d;
	int			tex_y;
	int			y;
	const int	tex_x = calculate_tex_x(stripe, info, texture);
	int			color;

	y = info->draw_start_y - 1;
	while (++y < info->draw_end_y)
	{
		d = y * 256 - cubed->scene.resol.height * 128 + info->sprite_height
			* 128;
		tex_y = ((d * texture->height) / info->sprite_height) / 256;
		color = texture->img.data[texture->width * tex_y + tex_x];
		if (is_not_transparent(color))
			draw_vertical_line(cubed, stripe, y, color);
	}
}

static void	draw_any_sprite(t_cubed *cubed, t_sprite_render_info *info,
		t_texture *texture)
{
	int	stripe;

	stripe = info->draw_start_x - 1;
	while (++stripe < info->draw_end_x)
	{
		if (info->transform_y > 0 && stripe > 0
			&& stripe < cubed->scene.resol.width)
		{
			draw_vertical_sprite_line(cubed, stripe, info, texture);
		}
	}
}

static void	draw_spawners(t_cubed *cubed)
{
	t_sprite_spawner	*spawner;
	int					i;

	i = -1;
	while (++i < cubed->scene.sprite_info.spawner_count)
	{
		spawner = &cubed->scene.sprite_info.spawners[i];
		draw_any_sprite(cubed, &spawner->info, &spawner->spawner_texture);
	}
}

static void	draw_moving_sprites(t_cubed *cubed)
{
	t_sprite	*sprite;

	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		draw_any_sprite(cubed, &sprite->info, &sprite->texture);
		sprite = sprite->next;
	}
}

void	draw_sprites(t_cubed *cubed)
{
	draw_spawners(cubed);
	draw_moving_sprites(cubed);
}