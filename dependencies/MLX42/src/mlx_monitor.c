/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:18:59 by W2Wizard          #+#    #+#             */
/*   Updated: 2024/05/25 04:49:01 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

void mlx42_get_monitor_size(int32_t index, int32_t* width, int32_t* height)
{
	MLX_ASSERT(index >= 0, "Index out of bounds");
	MLX_NONNULL(width);
	MLX_NONNULL(height);

	*width = 0;
	*height = 0;
	
	int32_t monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
	if (index > monitor_count || !monitors)
		return;

	const GLFWvidmode* vidmode;
	if ((vidmode = glfwGetVideoMode(monitors[index])))
	{
		*width = vidmode->width;
		*height = vidmode->height;
	}
}