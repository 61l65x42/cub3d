/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:53:08 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 00:56:11 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_rays(t_cubed *game)
{
	double	ray_angle;
	int		i;

	ray_angle = game->player.rotation_angle - game->rays.view_angle / 2;
	i = -1;
	while (++i < game->scene.resolution.width)
	{
		game->rays.ray_array[i].angle = ray_angle;
		cast_ray(&game->rays.ray_array[i], &game->scene.map, &game->player);
		ray_angle += game->rays.view_angle / game->scene.resolution.width;
	}
}
