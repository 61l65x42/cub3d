/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:15:35 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/23 07:49:23 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

# define MAX_WEAPONS 10
# include "display.h"

typedef struct s_cubed	t_cubed;

typedef struct s_weapon
{
	t_texture			texture;
	t_animation			shooting_animation;
}						t_weapon;

typedef struct s_weapon_map
{
	t_weapon			weapons[MAX_WEAPONS];
	int					current_weapon;
	int					total_weapons;
}						t_weapon_map;

int						handle_weapon_switch(int button, t_cubed *cubed);
void					load_weapons(t_cubed *cubed, void *mlx,
							t_weapon_map *weapon_map);
#endif