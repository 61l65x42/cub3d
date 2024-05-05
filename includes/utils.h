/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:37 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/05 19:19:02 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define ARG_ERROR_MSG "Remember to give the cub file name ./cub3d <example.cub>\n"
# define NOT_CUB_ERROR_MSG "The file is not a .cub file\n"
# define CUB_OPEN_ERROR_MSG "Error: .cub open()\n"
# define CUB_ERROR_COLOR \
	"Error: get_color_rgb()\
	- color value out of range\n"
# define CUB_ERROR_MALLOC "Error: malloc() in -> "
# define CUB_MAP_SPLIT_DELIMITERS " \n\t\v\f\r"
# define ERR_RGB "Error: get_color_rgb() - invalid rgb value\n"
# define ERR_RESOLUTION "Error: get_resolution() - invalid resolution value\n"

typedef struct s_cubed	t_cubed;

int						has_extension(char *file, char *ext);
void					ft_clean_exit(t_cubed *cubed, char *msg);
int						is_start_of_map(char *line);
void					free_2d_array(char **array);
int						ft_2d_array_len(char **array);
bool					is_valid_game_identifier(const char *identifier,
							char **data);
bool					is_valid_color_value(int *color, char *value);

#endif