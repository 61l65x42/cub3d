/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:24:56 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/06 19:02:57 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture(t_texture *texture)
{
	if (texture->path)
	{
		free(texture->path);
		texture->path = 0;
	}
	if (texture->img.img_ptr || texture->img.data)
	{
		free(texture->img.data);
		free(texture->img.img_ptr);
		texture->img.data = 0;
		texture->img.img_ptr = 0;
	}
}

static void	free_all_mlx(t_mlx *mlx)
{
	if (mlx->img.img_ptr || mlx->img.data)
	{
		free(mlx->img.data);
		free(mlx->img.img_ptr);
		mlx->img.data = 0;
		mlx->img.img_ptr = 0;
	}
	if (mlx->win)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		mlx->win = 0;
	}
	if (mlx->mlx_ptr)
	{
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = 0;
	}
}

void	ft_clean_exit(t_cubed *cubed, char *msg)
{
	if (cubed)
	{
		free_texture(&cubed->scene.north_texture);
		free_texture(&cubed->scene.south_texture);
		free_texture(&cubed->scene.east_texture);
		free_texture(&cubed->scene.west_texture);
		free_2d_array(cubed->scene.map.grid);
	}
	if (cubed->mlx.mlx_ptr)
		free_all_mlx(&cubed->mlx);
	if (msg)
		perror(msg);
	ft_memset(cubed, 0, sizeof(t_cubed));
	exit(EXIT_FAILURE);
}
