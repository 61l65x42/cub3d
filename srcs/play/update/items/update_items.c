/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:02:20 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 00:00:10 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		update_item_effects(t_player *p, double delta_time);

static void	remove_expired_items(t_cubed *cubed, t_item **current,
		t_item **prev)
{
	if (*prev)
		(*prev)->next = (*current)->next;
	else
		cubed->scene.sprite_info.item_info.items = (*current)->next;
	free(*current);
	if (*prev)
		*current = (*prev)->next;
	else
		*current = cubed->scene.sprite_info.item_info.items;
	cubed->scene.sprite_info.item_info.item_count--;
}

static void	update_active_item(t_cubed *cubed, t_item *item)
{
	const t_player	*p = &cubed->player;

	item->distance = get_distance(p->x, p->y, item->x, item->y);
	update_render_info(cubed, item->x, item->y, &item->info);
	item->time_since_drop += ITEM_TIME_INCREMENT;
	item->info.health_bar.health_percentage = (item->time_since_drop
			/ ITEM_DROP_LIFETIME);
}

void	pick_up_item(t_cubed *cubed, t_item **current, t_item **prev)
{
	t_player	*p;

	p = &cubed->player;
	if ((*current)->type == ITEM_HEALTH)
		p->health_bar.health_percentage = (float)(p->health += 30)
			/ (float)PLAYER_MAX_HEALTH;
	else if ((*current)->type == ITEM_BREAD)
		p->health_bar.health_percentage = (float)(p->health += 20)
			/ (float)PLAYER_MAX_HEALTH;
	else if ((*current)->type == ITEM_BOOTS)
	{
		if (p->effects.boots_effect_timer == 0)
			p->move_speed += 0.1;
		p->effects.boots_effect_timer = BOOTS_EFFECT_TIME;
	}
	else if ((*current)->type == ITEM_POISON)
		p->health_bar.health_percentage = (float)(p->health -= 20)
			/ (float)PLAYER_MAX_HEALTH;
	else if ((*current)->type == ITEM_CLOAK)
		p->effects.cloak_effect_timer = CLOAK_EFFECT_TIME;
	if (p->health > 100)
		p->health = 100;
	remove_expired_items(cubed, current, prev);
}

void	update_all_items(t_cubed *cubed)
{
	t_item	*i;
	t_item	*prev_i;

	i = cubed->scene.sprite_info.item_info.items;
	prev_i = NULL;
	while (i)
	{
		if (i->time_since_drop >= ITEM_DROP_LIFETIME)
		{
			remove_expired_items(cubed, &i, &prev_i);
		}
		else
		{
			update_active_item(cubed, i);
			if (i->distance <= ITEM_PICKUP_THRESHOLD)
				pick_up_item(cubed, &i, &prev_i);
			else
			{
				prev_i = i;
				i = i->next;
			}
		}
	}
	update_item_effects(&cubed->player, ITEM_TIME_INCREMENT);
}