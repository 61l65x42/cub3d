/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:52:48 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 14:25:04 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extract_scene(t_scenedata *scene, char **av)
{
	const int	fd = open(av[1], O_RDONLY);

	if (fd < 0)
		ft_clean_exit(CUB_OPEN_ERROR_MSG);
	close(fd);
}
