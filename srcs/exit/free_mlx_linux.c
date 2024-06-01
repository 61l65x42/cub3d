/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx_linux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:24:56 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 10:50:55 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_cubed *cubed)
{
	if (cubed->mlx.img.img_ptr)
		mlx_destroy_image(cubed->mlx.mlx_ptr, cubed->mlx.img.img_ptr);
	if (cubed->mlx.win)
		mlx_destroy_window(cubed->mlx.mlx_ptr, cubed->mlx.win);
	if (LINUX)
		mlx_destroy_display(cubed->mlx.mlx_ptr);
	if (LINUX && cubed->mlx.mlx_ptr)
	{
		free(cubed->mlx.mlx_ptr);
		cubed->mlx.mlx_ptr = 0;
	}
}
