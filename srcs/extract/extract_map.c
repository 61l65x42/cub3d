/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:21:38 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 17:07:58 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map(int fd, char *line, t_map *map)
{
	int		i;
	int		alloc_size;
	char	**tmp_map;

	i = 0;
	alloc_size = 2;
	tmp_map = malloc(alloc_size * sizeof(char *));
	if (!tmp_map)
		return (perror(CUB_ERROR_MALLOC "get_map()\n"), -1);
	while (1)
	{
		if (i >= alloc_size - 1)
		{
			alloc_size *= 2;
			tmp_map = ft_realloc(tmp_map, (i + 1) * sizeof(char *), alloc_size
					* sizeof(char *));
			if (!tmp_map)
				return (perror(CUB_ERROR_MALLOC "get_map()\n"), -1);
		}
		tmp_map[i++] = ft_strdup(line);
		if (!tmp_map[i - 1])
			return (perror(CUB_ERROR_MALLOC "get_map()\n"), -1);
		free(line);
		line = 0;
		if (!gnl(fd, &line) && *line == 0)
			break ;
	}
	free(line);
	tmp_map[i] = 0;
	map->grid = tmp_map;
	map->height = i;
	return (0);
}

static int	get_map_width(char **strs)
{
	size_t	max_length;
	size_t	length;
	int		i;
	int		j;

	max_length = 0;
	i = 0;
	while (strs[i])
	{
		length = 0;
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '\t')
				length += 4;
			else
				length++;
			j++;
		}
		if (length > max_length)
			max_length = length;
		i++;
	}
	return (max_length);
}

int	extract_map(t_cubed *cubed, int fd, char *line)
{
	int	status;

	status = 0;
	status = get_map(fd, line, &cubed->scene.map);
	if (status)
	{
		ft_fprintf(STDERR_FILENO, "extract_map() failed\n");
		return (status);
	}
	cubed->scene.map.width = get_map_width(cubed->scene.map.grid);
	return (status);
}
