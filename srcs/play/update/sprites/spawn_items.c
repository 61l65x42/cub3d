/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:20:55 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 20:22:14 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_item_probabilities(t_item_probability *probs)
{
	probs[0] = (t_item_probability){ITEM_NONE, 25};
	probs[1] = (t_item_probability){ITEM_HEALTH, 40};
	probs[2] = (t_item_probability){ITEM_POISON, 55};
	probs[3] = (t_item_probability){ITEM_BOOTS, 70};
	probs[4] = (t_item_probability){ITEM_CLOAK, 85};
	probs[5] = (t_item_probability){ITEM_BREAD, 100};
}

static t_item_probability	*get_probabilities(t_sprite_type entity_type)
{
	static int					initialized = 0;
	static t_item_probability	sprite_probs[ITEM_MAX + 1];
	static t_item_probability	spawner_probs[ITEM_MAX + 1];
	static t_item_probability	boss_probs[ITEM_MAX + 1];

	if (!initialized)
	{
		init_item_probabilities(sprite_probs);
		init_item_probabilities(spawner_probs);
		init_item_probabilities(boss_probs);
		initialized = 1;
	}
	if (entity_type == SPRITE)
		return (sprite_probs);
	else if (entity_type == SPAWNER)
		return (spawner_probs);
	else if (entity_type == BOSS)
		return (boss_probs);
	return (NULL);
}

static t_item_type	get_item_type(int *counter, t_sprite_type entity_type)
{
	const int			count = ITEM_MAX + 1;
	const int			threshold = (*counter * 100 / (count)) % 100;
	int					i;
	t_item_probability	*probabilities;

	probabilities = get_probabilities(entity_type);
	(*counter)++;
	i = -1;
	while (++i < ITEM_MAX + 1)
	{
		if (threshold < probabilities[i].cumulative_probability)
			return (probabilities[i].type);
	}
	return (probabilities[count - 1].type);
}

void	spawn_item(t_cubed *cubed, double x, double y,
		t_sprite_type entity_type)
{
	const t_item_type	type
		= get_item_type(&cubed->scene.sprite_info.item_info.\
		spawn_attempt_counter, entity_type);
	t_item_info			*i;
	t_item				*new_item;

	if (type == ITEM_NONE)
		return ;
	i = &cubed->scene.sprite_info.item_info;
	new_item = ft_calloc(1, sizeof(t_item));
	if (!new_item)
		ft_clean_exit(cubed, ERR_ITEM_MALLOC, 0);
	new_item->type = type;
	new_item->x = x;
	new_item->y = y;
	new_item->time_since_drop = 0;
	new_item->distance = get_distance(cubed->player.x, cubed->player.y, x, y);
	new_item->next = i->items;
	update_render_info(cubed, x, y, &new_item->info);
	i->items = new_item;
	i->item_count++;
}
