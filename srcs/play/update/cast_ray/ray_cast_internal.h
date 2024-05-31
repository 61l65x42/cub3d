/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:24:01 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/31 12:59:26 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_INTERNAL_H
# define RAY_CAST_INTERNAL_H

typedef struct s_raycast_helper
{
	double				x_step;
	double				y_step;
	double				ray_section;
	int					is_south_direction;
	int					is_east_direction;
}						t_raycast_helper;

#endif