/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:19:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 11:54:16 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_akimbos_shooting(t_cubed *cubed)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	const t_ray	*middle_ray = &cubed->rays.ray_array[middle_ray_index];
	const int	map_x = (int)middle_ray->x;
	const int	map_y = (int)middle_ray->y;
	t_sprite	*sprite;
	t_sprite	*prev_sprite;

	sprite = cubed->scene.sprite_info.sprites;
	prev_sprite = NULL;
	while (sprite)
	{
		if ((int)sprite->x == map_x && (int)sprite->y == map_y)
		{
			apply_damage_to_sprite(cubed, sprite, prev_sprite, 10);
			return ;
		}
		prev_sprite = sprite;
		sprite = sprite->next;
	}
	if (t_map_get(&cubed->scene.map, map_x, map_y) == '1')
	{
		t_map_insert(&cubed->scene.map, map_x, map_y, '0');
	}
}

static void	handle_wrench_shooting(t_cubed *cubed)
{
	const float	distance = 3.0;
	const float	dir_x = cubed->player.dir_x * distance;
	const float	dir_y = cubed->player.dir_y * distance;
	const int	map_x = (int)(cubed->player.x + dir_x);
	const int	map_y = (int)(cubed->player.y + dir_y);

	if (t_map_get(&cubed->scene.map, map_x, map_y) == '0')
	{
		t_map_insert(&cubed->scene.map, map_x, map_y, '1');
	}
}

static void	destroy_adjacent_walls(t_cubed *cubed, int map_x, int map_y,
		int depth)
{
	int	dx;
	int	dy;

	if (depth == 4 || t_map_get(&cubed->scene.map, map_x, map_y) != '1')
		return ;
	t_map_insert(&cubed->scene.map, map_x, map_y, '0');
	depth = depth + 1;
	dx = -2;
	while (++dx <= 1)
	{
		dy = -2;
		while (++dy <= 1)
		{
			if (dx != 0 || dy != 0)
				destroy_adjacent_walls(cubed, map_x + dx, map_y + dy, depth);
		}
	}
}

static void	handle_raygun_shooting(t_cubed *cubed)
{
	const int	middle_ray_index = cubed->scene.resol.width / 2;
	const t_ray	*middle_ray = &cubed->rays.ray_array[middle_ray_index];
	const int	map_x = (int)middle_ray->x;
	const int	map_y = (int)middle_ray->y;
	t_sprite	*sprite;
	t_sprite	*prev_sprite;

	sprite = cubed->scene.sprite_info.sprites;
	prev_sprite = NULL;
	while (sprite)
	{
		if ((int)sprite->x == map_x && (int)sprite->y == map_y)
		{
			apply_damage_to_sprite(cubed, sprite, prev_sprite, 10);
			return ;
		}
		prev_sprite = sprite;
		sprite = sprite->next;
	}
	if (t_map_get(&cubed->scene.map, map_x, map_y) == '1')
	{
		destroy_adjacent_walls(cubed, map_x, map_y, 0);
	}
}

void	handle_shooting(t_cubed *cubed)
{
	const t_weapon_map	*weapon_map = &cubed->weapon_map;
	const t_weapon		*current_weapon = &weapon_map->weapons[weapon_map->current_weapon];

	if (current_weapon->type == WEAPON_AKIMBOS)
	{
		handle_akimbos_shooting(cubed);
	}
	else if (current_weapon->type == WEAPON_WRENCH)
	{
		handle_wrench_shooting(cubed);
	}
	else if (current_weapon->type == WEAPON_RAYGUN)
	{
		handle_raygun_shooting(cubed);
	}
	else if (current_weapon->type == WEAPON_MINIGUN)
	{
		handle_akimbos_shooting(cubed);
	}
	if (current_weapon->type != WEAPON_MINIGUN
		&& current_weapon->type != WEAPON_WRENCH)
	{
		cubed->player.shooting = 0;
	}
}
