/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_renderables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:52:03 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 11:45:52 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "renderable.h"

t_renderable	*collect_wall_renderables(t_cubed *cubed,
		t_renderable *renderables, int *idx)
{
	int		i;
	t_ray	*ray;

	i = 0;
	while (i < cubed->rays.ray_count)
	{
		ray = &cubed->rays.ray_array[i];
		renderables[*idx].distance = ray->distance;
		renderables[*idx].type = RENDERABLE_WALL;
		renderables[*idx].data.ray = ray;
		(*idx)++;
		i++;
	}
	return (renderables);
}

t_renderable	*collect_spawner_renderables(t_cubed *cubed,
		t_renderable *renderables, int *idx)
{
	t_sprite_spawner	*spawner;

	spawner = cubed->scene.sprite_info.spawners;
	while (spawner)
	{
		renderables[*idx].distance = spawner->distance;
		renderables[*idx].type = RENDERABLE_SPAWNER;
		renderables[*idx].data.spawner = spawner;
		(*idx)++;
		spawner = spawner->next;
	}
	return (renderables);
}

t_renderable	*collect_sprite_renderables(t_cubed *cubed,
		t_renderable *renderables, int *idx)
{
	t_sprite	*sprite;

	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		renderables[*idx].distance = sprite->distance;
		renderables[*idx].type = RENDERABLE_SPRITE;
		renderables[*idx].data.sprite = sprite;
		(*idx)++;
		sprite = sprite->next;
	}
	return (renderables);
}

t_renderable	*collect_door_renderables(t_cubed *cubed,
		t_renderable *renderables, int *idx)
{
	t_door	*door;

	door = cubed->scene.sprite_info.doors;
	while (door)
	{
		renderables[*idx].distance = door->distance;
		renderables[*idx].type = RENDERABLE_DOOR;
		renderables[*idx].data.door = door;
		(*idx)++;
		door = door->next;
	}
	return (renderables);
}

t_renderable	*collect_renderables(t_cubed *cubed, int *count)
{
	int				total_count;
	t_renderable	*renderables;
	int				idx;
	t_sprite		*sprite;
	t_door			*door;

	total_count = cubed->rays.ray_count
		+ cubed->scene.sprite_info.spawner_count;
	sprite = cubed->scene.sprite_info.sprites;
	while (sprite)
	{
		total_count++;
		sprite = sprite->next;
	}
	door = cubed->scene.sprite_info.doors;
	while (door)
	{
		total_count++;
		door = door->next;
	}
	renderables = malloc(total_count * sizeof(t_renderable));
	if (!renderables)
		ft_clean_exit(cubed, "Failed to allocate memory for renderables", 0);
	idx = 0;
	renderables = collect_wall_renderables(cubed, renderables, &idx);
	renderables = collect_spawner_renderables(cubed, renderables, &idx);
	renderables = collect_sprite_renderables(cubed, renderables, &idx);
	renderables = collect_door_renderables(cubed, renderables, &idx);
	*count = idx;
	return (renderables);
}
