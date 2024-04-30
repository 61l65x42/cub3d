/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:52:48 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 16:54:37 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	extract_data(t_scenedata *scene, char *line)
{
}

void	extract_scene(t_scenedata *scene, char **av)
{
	const int	fd = open(av[1], O_RDONLY);
	char		*line;

	if (fd < 0)
		ft_clean_exit(CUB_OPEN_ERROR_MSG);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_start_of_map(line))
		{
			extract_map(scene, fd, line);
			break ;
		}
		else
			extract_data(scene, line);
	}
	close(fd);
}
