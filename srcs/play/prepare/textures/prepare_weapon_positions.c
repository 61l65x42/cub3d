/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_positions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:15:27 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 12:09:35 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize_akimbos_positions(t_weapon *weapon, t_cubed *cubed)
{
	weapon->gun_pos_x = (cubed->scene.resol.width - weapon->texture.width) / 2;
	weapon->gun_pos_y = cubed->scene.resol.height - weapon->texture.height + 50;
	weapon->left_gun_tip_x = weapon->gun_pos_x + weapon->texture.width * 0.2;
	weapon->right_gun_tip_x = weapon->gun_pos_x + weapon->texture.width * 0.78;
	weapon->gun_tip_y = weapon->gun_pos_y + weapon->texture.height * 0.3;
}

static void	initialize_hammer_positions(t_weapon *weapon, t_cubed *cubed)
{
	weapon->gun_pos_x = (cubed->scene.resol.width - weapon->texture.width) / 2;
	weapon->gun_pos_y = cubed->scene.resol.height - weapon->texture.height + 60;
	weapon->left_gun_tip_x = weapon->gun_pos_x + weapon->texture.width * 0.1;
	weapon->right_gun_tip_x = weapon->gun_pos_x + weapon->texture.width * 0.9;
	weapon->gun_tip_y = weapon->gun_pos_y + weapon->texture.height * 0.4;
}

static void	initialize_raygun_positions(t_weapon *weapon, t_cubed *cubed)
{
	weapon->gun_pos_x = (cubed->scene.resol.width - weapon->texture.width) / 2;
	weapon->gun_pos_y = cubed->scene.resol.height - weapon->texture.height + 40;
	weapon->left_gun_tip_x = weapon->gun_pos_x + weapon->texture.width * 0.15;
	weapon->right_gun_tip_x = weapon->left_gun_tip_x;
	weapon->gun_tip_y = weapon->gun_pos_y + weapon->texture.height * 0.10;
}

static void	initialize_minigun_positions(t_weapon *weapon, t_cubed *cubed)
{
	weapon->gun_pos_x = (cubed->scene.resol.width - weapon->texture.width) / 2;
	weapon->gun_pos_y = cubed->scene.resol.height - weapon->texture.height + 50;
	weapon->left_gun_tip_x = weapon->gun_pos_x + weapon->texture.width * 0.5;
	weapon->right_gun_tip_x = weapon->left_gun_tip_x;
	weapon->gun_tip_y = weapon->gun_pos_y + weapon->texture.height * 0.52;
}

void	get_gun_positions(t_weapon *weapon, t_cubed *cubed, int i)
{
	const t_weapon_type	weapon_types[WEAPON_MAX] = {WEAPON_AKIMBOS,
		WEAPON_WRENCH, WEAPON_RAYGUN, WEAPON_MINIGUN};

	weapon->type = weapon_types[i];
	if (weapon->type == WEAPON_AKIMBOS)
	{
		initialize_akimbos_positions(weapon, cubed);
	}
	else if (weapon->type == WEAPON_WRENCH)
	{
		initialize_hammer_positions(weapon, cubed);
	}
	else if (weapon->type == WEAPON_RAYGUN)
	{
		initialize_raygun_positions(weapon, cubed);
	}
	else if (weapon->type == WEAPON_MINIGUN)
	{
		initialize_minigun_positions(weapon, cubed);
	}
}