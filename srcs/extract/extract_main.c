/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:16:13 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/16 17:09:52 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		extract_scene(t_cubed *cubed, char *line);
int		extract_map(t_cubed *cubed, int fd, char *line);

void	extract_from_cub_file(t_cubed *cubed, const char *path)
{
	const int	fd = open(path, O_RDONLY);
	int			status;
	int			gnl_ret;
	char		*line;

	if (fd < 0)
		ft_clean_exit(cubed, "extract_from_cub() open()");
	status = 0;
	gnl_ret = gnl(fd, &line);
	while (gnl_ret > 0)
	{
		if (is_start_of_map(line))
			break ;
		status = extract_scene(cubed, line);
		free(line);
		if (status)
			break ;
		gnl_ret = gnl(fd, &line);
	}
	if (!status && gnl_ret == 1)
		status = extract_map(cubed, fd, line);
	close(fd);
	if (status)
		ft_clean_exit(cubed, "extract_from_cub():");
}
