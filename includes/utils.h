/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:37 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/06 17:05:02 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "definitions.h"
# include "libft.h"

typedef struct s_cubed	t_cubed;

int						has_extension(char *file, char *ext);
void					ft_clean_exit(t_cubed *cubed, char *msg);
int						is_start_of_map(char *line);
void					free_2d_array(char **array);
int						ft_2d_array_len(char **array);
bool					is_valid_game_identifier(const char *identifier,
							char **data);
bool					is_valid_color_value(int *color, char *value);
bool					does_texture_exist(char *texture_path,
							char *texture_name);

#endif